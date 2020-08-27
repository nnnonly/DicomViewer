#include "pch.h"
#include "AppDocument.h"

AppDocument* AppDocument::instance = NULL;

AppDocument* AppDocument::getInstance()
{
	if (instance == NULL)
	{
		instance = new AppDocument();
	}
	return instance;
}

void AppDocument::setDicomPath(std::string &dicomPath)
{
	AppDocument::dicomPath = dicomPath;
}

const std::string &AppDocument::getDicomPath()
{
	return dicomPath;
}

const cv::Mat &AppDocument::getMatImage()
{
	return dicomImageConvertMat;
}

void AppDocument::setMatImage(cv::Mat inImg)
{
	dicomImageConvertMat = inImg;
}

const int AppDocument::getRow()
{
	return dicomImageConvertMat.rows;
}

const int AppDocument::getColumn()
{
	return dicomImageConvertMat.cols;
}

void AppDocument::setWidth(const std::string &window_width)
{
	AppDocument::window_width = window_width;
}

void AppDocument::setRowPS(const std::string &row_pixelspacing)
{
	AppDocument::row_pixelspacing = row_pixelspacing;
}

const std::string &AppDocument::getRowPS()
{
	return row_pixelspacing;
}

void AppDocument::setColPS(const std::string &col_pixelspacing)
{
	AppDocument::col_pixelspacing = col_pixelspacing;
}

const std::string &AppDocument::getColPS()
{
	return col_pixelspacing;
}

const std::string &AppDocument::getWidth()
{
	return window_width;
}

void AppDocument::setCenter(const std::string &window_center)
{
	AppDocument::window_center = window_center;
}


const std::string &AppDocument::getCenter()
{
	return window_center;
}

void AppDocument::setPointPlus(std::vector<cv::Point2f> &pointPlus)
{
	AppDocument::centerPointPlus = pointPlus;
}

std::vector<cv::Point2f> &AppDocument::getPointPlus()
{
	return centerPointPlus;
}

void AppDocument::setPointMulti(std::vector<cv::Point2f> &pointMulti)
{
	AppDocument::centerPointMulti = pointMulti;
}

std::vector<cv::Point2f> &AppDocument::getPointMulti()
{
	return centerPointMulti;
}