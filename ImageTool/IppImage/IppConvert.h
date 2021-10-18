#include <opencv2\opencv.hpp>
#pragma once

#include "IppImage.h"
#include "IppDib.h"

void IppDibToImage(IppDib& dib, IppByteImage& img);
void IppDibToImage(IppDib& dib, IppRgbImage& img);

void IppImageToDib(IppByteImage& img, IppDib& dib);
void IppImageToDib(IppFloatImage& img, IppDib& dib);
void IppImageToDib(IppRgbImage& img, IppDib& dib);

void IppImageToMat(IppByteImage& img, cv::Mat& mat);
void IppImageToMat(IppRgbImage& img, cv::Mat& mat);

void IppMatToImage(cv::Mat& mat, IppByteImage& img);
void IppMatToImage(cv::Mat& mat, IppRgbImage& img);