#include "pch.h"
#include "DetectDlg.h"

void AFX_EXT_CLASS DetectDlg::IppHarrisCorner(IppByteImage& img, std::vector<IppPoint>& corners, double th)
{
	register int i, j, x, y;

	int w = img.GetWidth();
	int h = img.GetHeight();

	BYTE** ptr = img.GetPixels2D();

	//-------------------------------------------------------------------------
	// 1. (fx)*(fx), (fx)*(fy), (fy)*(fy) 계산
	//-------------------------------------------------------------------------

	IppFloatImage imgDx2(w, h);
	IppFloatImage imgDy2(w, h);
	IppFloatImage imgDxy(w, h);

	float** dx2 = imgDx2.GetPixels2D();
	float** dy2 = imgDy2.GetPixels2D();
	float** dxy = imgDxy.GetPixels2D();

	float tx, ty;
	for (j = 1; j < h - 1; j++)
		for (i = 1; i < w - 1; i++)
		{
			tx = (ptr[j - 1][i + 1] + ptr[j][i + 1] + ptr[j + 1][i + 1]
				- ptr[j - 1][i - 1] - ptr[j][i - 1] - ptr[j + 1][i - 1]) / 6.f;
			ty = (ptr[j + 1][i - 1] + ptr[j + 1][i] + ptr[j + 1][i + 1]
				- ptr[j - 1][i - 1] - ptr[j - 1][i] - ptr[j - 1][i + 1]) / 6.f;

			dx2[j][i] = tx * tx;
			dy2[j][i] = ty * ty;
			dxy[j][i] = tx * ty;
		}

	//-------------------------------------------------------------------------
	// 2. 가우시안 필터링
	//-------------------------------------------------------------------------

	IppFloatImage imgGdx2(w, h);
	IppFloatImage imgGdy2(w, h);
	IppFloatImage imgGdxy(w, h);

	float** gdx2 = imgGdx2.GetPixels2D();
	float** gdy2 = imgGdy2.GetPixels2D();
	float** gdxy = imgGdxy.GetPixels2D();

	float g[5][5] = { { 1, 4, 6, 4, 1 },{ 4, 16, 24, 16, 4 },
		{ 6, 24, 36, 24, 6 },{ 4, 16, 24, 16, 4 },{ 1, 4, 6, 4, 1 } };

	for (y = 0; y < 5; y++)
		for (x = 0; x < 5; x++)
		{
			g[y][x] /= 256.f;
		}

	float tx2, ty2, txy;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			tx2 = ty2 = txy = 0;
			for (y = 0; y < 5; y++)
				for (x = 0; x < 5; x++)
				{
					tx2 += (dx2[j + y - 2][i + x - 2] * g[y][x]);
					ty2 += (dy2[j + y - 2][i + x - 2] * g[y][x]);
					txy += (dxy[j + y - 2][i + x - 2] * g[y][x]);
				}

			gdx2[j][i] = tx2;
			gdy2[j][i] = ty2;
			gdxy[j][i] = txy;
		}

	//-------------------------------------------------------------------------
	// 3. 코너 응답 함수 생성
	//-------------------------------------------------------------------------

	IppFloatImage imgCrf(w, h);
	float** crf = imgCrf.GetPixels2D();

	float k = 0.04f;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			crf[j][i] = (gdx2[j][i] * gdy2[j][i] - gdxy[j][i] * gdxy[j][i])
				- k * (gdx2[j][i] + gdy2[j][i]) * (gdx2[j][i] + gdy2[j][i]);
		}

	//-------------------------------------------------------------------------
	// 4. 임계값보다 큰 국지적 최대값을 찾아 코너 포인트로 결정
	//-------------------------------------------------------------------------

	corners.clear();
	float cvf_value;
	for (j = 2; j < h - 2; j++)
		for (i = 2; i < w - 2; i++)
		{
			cvf_value = crf[j][i];
			if (cvf_value > th)
			{
				if (cvf_value > crf[j - 1][i] && cvf_value > crf[j - 1][i + 1] &&
					cvf_value > crf[j][i + 1] && cvf_value > crf[j + 1][i + 1] &&
					cvf_value > crf[j + 1][i] && cvf_value > crf[j + 1][i - 1] &&
					cvf_value > crf[j][i - 1] && cvf_value > crf[j - 1][i - 1])
				{
					corners.push_back(IppPoint(i, j));
					//Rectangle(corners, i - 100, j - 100, i + 100, j + 100);
				}
			}
		}
}
