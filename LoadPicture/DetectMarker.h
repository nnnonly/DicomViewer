#pragma once
#include "CoreInclude.h"
#include "AppDocument.h"
namespace DetectMarker
{
	void preProcessing(const cv::Mat & img);

	void featureExtraction(const cv::Mat& img, cv::Mat& mask_plus, cv::Mat& mask_multi, std::vector<cv::Point2f> &centerPointPlus, std::vector<cv::Point2f> &centerPointMulti);

	std::vector<cv::Point2f> postProcessingPlus(const cv::Mat& imgIn, std::vector<cv::Point2f> &centerPoint);

	std::vector<cv::Point2f> postProcessingMulti(const cv::Mat& imgIn, std::vector<cv::Point2f> &centerPoint);

	void GeneratePlusMask(cv::Mat& mask_plus, double rowPS, double colPS, int height, int width);

	void GenerateMultiMask(cv::Mat& mask_multi, double rowPS, double colPS, int height, int width);

	void drawMarkerPlus(const cv::Mat &outputImg, std::vector<cv::Point2f> &Point);

	void drawMarkerMulti(const cv::Mat &outputImg, std::vector<cv::Point2f> &Point);

	void showImageDebug(const cv::Mat& imageDebug, std::string nameWindow);
}