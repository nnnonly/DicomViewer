#pragma once
#include "CoreInclude.h"
#include "AppDocument.h"
#include<string>

namespace DisplayLUT
{
	void loadPixel(int windowWidth, int windowCenter, const cv::Mat&img, cv::Mat & outputImage);

}

