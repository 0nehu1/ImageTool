#include "pch.h"
#include "DetectDlg.h"
#include "..\ImageTool\CHarrisCornerDlg.h"
#include "dllmain.cpp"
#include "..\ImageTool\ImageToolDoc.h"
#include "..\ImageTool\ImageToolDoc.cpp"

void AFX_EXT_CLASS DetectDlg::DllHarrisCorner()
{
	CHarrisCornerDlg dlg;

	//HDC h_dc = ::GetDC(NULL);

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib1, img)
		std::vector<IppPoint> corners;
	IppHarrisCornerDLL(img, corners, dlg.m_nHarrisTh);

	BYTE** ptr = img.GetPixels2D();

	//RECT rect;

	int x, y;
	for (IppPoint cp : corners)
	{
		x = cp.x;
		y = cp.y;

		//ptr[y - 1][x - 1] = ptr[y - 1][x] = ptr[y - 1][x + 1] = 255;
		//ptr[y][x - 1] = ptr[y][x] = ptr[y][x + 1] = 255;
		//ptr[y + 1][x - 1] = ptr[y + 1][x] = ptr[y + 1][x + 1] = 255;

		ptr[y - 2][x - 2] = 255;
		ptr[y + 2][x - 2] = 255;
		ptr[y - 2][x + 2] = 255;
		ptr[y + 2][x + 2] = 255;

		//Rectangle(h_dc,x - 10, y - 10, x + 10, y + 10);
		//Rectangle(x - 10 y - 10, x + 10, y + 10);
		//(x - 10, y - 10, x + 10, y + 10, RGB(255, 0, 0));
	}

	CONVERT_IMAGE_TO_DIB(img, dib)

		AfxNewBitmap(dib);
}
