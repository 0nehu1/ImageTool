#pragma once
#include <vector>
#include "..\ImageTool\IppImage\IppImage.h"
#include "..\ImageTool\IppImage\IppFeature.h"
class DetectDlg
{
	void AFX_EXT_CLASS IppHarrisCorner(IppByteImage& img, std::vector<IppPoint>& corners, double th);
};

