#include "pch.h"
#include "DetectMarker.h"

const float minPlus = 0.85;
const float minMulti = 0.7;
const float max = 1.0;

void DetectMarker::featureExtraction(const cv::Mat & img, cv::Mat& mask_plus, cv::Mat& mask_multi, std::vector<cv::Point2f> &centerPointPlus, std::vector<cv::Point2f> &centerPointMulti)
{
	cv::Mat result = img.clone();
	//cv::cvtColor(result, result, CV_GRAY2BGR);

	cv::normalize(result, result, 0, 1, cv::NORM_MINMAX, CV_32F);

	cv::Mat convPlus;
	cv::filter2D(result, convPlus, -1, mask_plus);

	cv::normalize(convPlus, convPlus, 0, 1, cv::NORM_MINMAX, CV_32F);

	//showImageDebug(convPlus, "Convolution");

	cv::inRange(convPlus, minPlus, max, convPlus);

	//showImageDebug(convPlus, "Threshold");
	
	std::vector<std::vector<cv::Point> > contours_plus;
	std::vector<cv::Vec4i> hierarchy_plus;
	cv::findContours(convPlus, contours_plus, hierarchy_plus, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	for (int i = 0; i < contours_plus.size(); i++)
	{
		auto mu_plus = cv::moments(contours_plus[i], false);
		centerPointPlus.push_back(cv::Point2f(mu_plus.m10 / mu_plus.m00, mu_plus.m01 / mu_plus.m00));
	}

	cv::Mat convMulti;
	cv::filter2D(result, convMulti, -1, mask_multi);

	cv::normalize(convMulti, convMulti, 0, 1, cv::NORM_MINMAX, CV_32F);
	cv::inRange(convMulti, minMulti, max, convMulti);

	std::vector<std::vector<cv::Point> > contours_multi;

	cv::findContours(convMulti, contours_multi, hierarchy_plus, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	for (int i = 0; i < contours_multi.size(); i++)
	{
		auto mu_multi = cv::moments(contours_multi[i], false);
		centerPointMulti.push_back(cv::Point2f(mu_multi.m10 / mu_multi.m00, mu_multi.m01 / mu_multi.m00));
	}

	//cv::imshow("detectPlus", convPlus);
	//cv::imshow("detectMulti", convMulti);

}