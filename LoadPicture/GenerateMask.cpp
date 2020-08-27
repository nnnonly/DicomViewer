#include "pch.h"
#include "DetectMarker.h"

void DetectMarker::GeneratePlusMask(cv::Mat& mask_plus, double rowPS, double colPS, int height, int width) 
{
	int ker_rows = width / rowPS;
	int ker_cols = height / colPS;

	cv::Mat kernel_plus = cv::Mat::zeros(ker_rows, ker_cols, CV_32F);
	
	cv::line(kernel_plus, cv::Point(ker_rows/2, 0), cv::Point(ker_rows/2, ker_rows-1), 1, 4);
	cv::line(kernel_plus, cv::Point(0, ker_cols /2), cv::Point(ker_cols  - 1, ker_cols/2), 1, 4);
	cv::circle(kernel_plus, cv::Point(ker_rows/2, ker_cols/2), 2, 0, 4);

	mask_plus = kernel_plus;
}

void DetectMarker::GenerateMultiMask(cv::Mat& mask_multi, double rowPS, double colPS, int height, int width)
{
	int ker_rows = width / rowPS;
	int ker_cols = height / colPS;

	cv::Mat kernel_multi = cv::Mat::zeros(ker_rows, ker_cols, CV_32F);
	cv::line(kernel_multi, cv::Point(0, 0), cv::Point(ker_rows - 1, ker_cols - 1), 1, 4);
	cv::line(kernel_multi, cv::Point(ker_rows - 1, 0), cv::Point(0, ker_cols - 1), 1, 4);
	
	cv::circle(kernel_multi, cv::Point(ker_rows / 2, ker_cols / 2), 2, 0, 4);
	mask_multi = kernel_multi;
}