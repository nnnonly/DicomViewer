#pragma once
#include "Dicom.h"
#include <string>

namespace WindowController
{
	std::string loadPath(CFileDialog& dlg);
	std::vector<std::string> split(std::string s, std::string delimiter);
	int loadInforImage(std::string path, cv::Mat &imag, Dicom &saveData);

};

