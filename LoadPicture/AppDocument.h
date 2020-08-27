#pragma once

#ifndef APPDOCUMENT_H
#define APPDOCUMENT_H


#include "CoreInclude.h"
class AppDocument
{
private:

	//~AppDocument();
	static AppDocument* instance;

	std::string dicomPath;
	cv::Mat dicomImageConvertMat;
	std::string window_width;
	std::string window_center;
	std::string row_pixelspacing;
	std::string col_pixelspacing;
	std::vector<cv::Point2f> centerPointPlus;
	std::vector<cv::Point2f> centerPointMulti;

public:

	static AppDocument* getInstance();

	void setDicomPath(std::string &dicomPath);

	const std::string &getDicomPath();

	const cv::Mat &getMatImage();

	void setMatImage(cv::Mat inImg);

	const int getRow();

	const int getColumn();

	void setWidth(const std::string &window_width);

	const std::string &getWidth();

	void setCenter(const std::string &window_center);

	const std::string &getCenter();

	void setRowPS(const std::string &row_pixelspacing);
	
	const std::string &getRowPS();

	void setColPS(const std::string &col_pixelspacing);

	const std::string &getColPS();

	void setPointPlus (std::vector<cv::Point2f> &pointPlus);

	std::vector<cv::Point2f> &getPointPlus();

	void setPointMulti(std::vector<cv::Point2f> &pointMulti);

	std::vector<cv::Point2f> &getPointMulti();

};

#endif //APPDOCUMENT_H