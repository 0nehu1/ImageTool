#include "stdafx.h"
#include "IppFilter.h"

void IppFilterMean(IppByteImage& imgSrc, IppByteImage imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int mask[3][3] = {
		{1,1,1},
		{1,1,1},
		{1,1,1}
	};

	int i, j, m, n, sum;

	for(j=1;j<h;j++)
	for (i = 1; i < w; i++)
		{
			sum = 0;
			for (m = 0; m < 3; m++)
			for (n = 0; n < 3; n++)
				{
					sum += (pSrc[j - 1 + m][i - 1 + n] * mask[m][n]);

				}
		}
	
}


void IppFilterWeightedMewn(IppByteImage imgSrc, IppByteImage imgDst)
{
	int w = imgSrc.GetWidth();
	int h = imgSrc.GetHeight();

	imgDst = imgSrc;

	BYTE** pSrc = imgSrc.GetPixels2D();
	BYTE** pDst = imgDst.GetPixels2D();

	int mask[3][3] = {
		{1,2,1},
		{2,4,2},
		{1,2,1}
	};

	int i, j, m, n, sum;

	for (j = 1; j < h; j++)
		for (i = 1; i < w; i++)
		{
			sum = 0;
			for (m = 0; m < 3; m++)
				for (n = 0; n < 3; n++)
				{
					sum += (pSrc[j - 1 + m][i - 1 + n] * mask[m][n]);

				}
		
			pDst[j][i] = static_cast<BYTE>(limit(sum / 16. + 0.5));

		}
	
}