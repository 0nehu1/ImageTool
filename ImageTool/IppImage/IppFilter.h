#pragma once

#include "IppImage.h"

void IppFilterMean(IppByteImage& imgSrc, IppByteImage imgDst);
void IppFilterWeightedMewn(IppByteImage imgSrc, IppByteImage imgDst);