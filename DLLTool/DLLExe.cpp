#include "pch.h"
#include "DLLExe.h"

#include "..\ImageTool\IppImage\IppFeature.h"
//#include "..\ImageTool\ImageTool.h"

#include "..\ImageTool\IppImage\IppConvert.h"
#include "dllmain.cpp"


#define CONVERT_DIB_TO_RGBIMAGE(m_Dib,img)\
	IppRgbImage img;\
	IppDibToImage(m_Dib,img);
#define SHOW_SPECTRUM_PHASE_IMAGE



#define CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)\
IppByteImage img;\
IppDibToImage(m_Dib,img);

#define CONVERT_IMAGE_TO_DIB(img, dib)\
IppDib dib;\
IppImageToDib(img,dib);

void DLLExe::Test112()
{
	

	HDC h_dc = ::GetDC(NULL);

	CONVERT_DIB_TO_BYTEIMAGE(m_Dib, img)
		std::vector<IppPoint> corners;
	IppHarrisCornerDLL(img, corners, 20);

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


		//AfxNewBitmap(dib);

}
