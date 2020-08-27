#include "pch.h"
#include "DetectMarker.h"
#define PI 3.14159265


const int threshold_min = 70;
const int threshold_max = 150;

void rotate(const cv::Mat& src, float angle)
{
	cv::Mat dst;
	cv::Point2f pt(src.cols / 2., src.rows / 2.);
	cv::Mat r = getRotationMatrix2D(pt, angle, 1.0);
	warpAffine(src, src, r, cv::Size(src.cols, src.rows));
	//return dst;
}

float rotateImg(const cv::Mat &src)
{
	cv::Mat outImg = src.clone();
	cv::medianBlur(src, src, 3);
	cv::GaussianBlur(src, src, cv::Size(3, 3), 0);
	cv::Mat dst, cdst;
	Canny(src, dst, 70, 150);

	cvtColor(dst, cdst, CV_GRAY2BGR);


	std::vector<cv::Vec4i> lines;
	HoughLinesP(dst, lines, 1, CV_PI / 180, 100, 50, 10);
	for (size_t i = 0; i < lines.size(); i++)
	{
		cv::Vec4i l = lines[i];
		cv::line(cdst, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(0, 0, 255), 3, CV_AA);
	}
	std::vector<float> outDegree;
	for (size_t i = 0; i < lines.size() - 1; i++)
	{
		int epsilon = 3;
		cv::Vec4i line1 = lines[i];
		float vector1x = abs(line1[0] - line1[2]);
		float vector1y = abs(line1[1] - line1[3]);

		float result = atan2(vector1y, vector1x) * 180 / PI;
		outDegree.push_back(std::min(result, 180 - result));
	}

	int out[1000];
	out[0] = 1;
	int lmax;
	for (int i = 0; i < outDegree.size(); i++)
	{
		lmax = 0;
		for (int j = 0; j < i; j++)
		{
			if (abs(outDegree[i] - outDegree[j]) <= 3)
			{
				if (out[j] > lmax)
				{
					lmax = out[j];
				}
			}
		}
		out[i] = lmax + 1;
	}
	int max = out[0];
	int maxIndex = 0;
	for (int i = 1; i < 1000; i++)
	{
		if (max < out[i])
		{
			max = out[i];
			maxIndex = i;
		}
	}
	/*cv::Mat abc;
	int maxValue = static_cast<int>(outDegree[maxIndex]);
	abc = rotate(outImg, outDegree[maxIndex]);*/
	return outDegree[maxIndex];
}

void DetectMarker::preProcessing(const cv::Mat& img) 
{
	//cv::blur(img, img, cv::Size(3,3));
	cv::medianBlur(img, img, 3);

	cv::GaussianBlur(img, img, cv::Size(3, 3), 0);

	//showImageDebug(img, "Noise Reduce");

	cv::Canny(img, img, threshold_min, threshold_max);

	//showImageDebug(img, "Canny");

	cv::Mat kernel_01 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5), cv::Point(2, 2));
	cv::morphologyEx(img, img, cv::MORPH_CLOSE, kernel_01);

	cv::Mat kernel_02 = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(3, 3), cv::Point(1, 1));
	cv::morphologyEx(img, img, cv::MORPH_OPEN, kernel_02); 

	//showImageDebug(img, "Morphology");

	//rotate(img, rotateImg(img));

	//showImageDebug(img, "Rotate");
}