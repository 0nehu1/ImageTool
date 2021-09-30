#include "IppColor.h"
#include "IppEnhance.h"
#include "IppFeature.h"

const double PI = 3.14159265358979323846;
const float  PI_F = 3.14159265358979323846f;

void IppInverse(IppRgbImage& img)
{
	int size = img.GetSize();
	RGBBYTE* p = img.GetPixels();

	for (int i = 0; i < size; i++)
	{
		p[i].r = 255 - p[i].r;
		p[i].g = 255 - p[i].g;
		p[i].b = 255 - p[i].b;
	}
}


