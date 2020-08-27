#pragma once

#ifndef DICOM_H
#define DICOM_H

#include "CoreInclude.h"

#include <string>
#include <map>

class Dicom
{
private:
	std::string file_name;
	std::string patient_name;
	std::string patient_id;
	std::string patient_DOB;
	std::string patient_sex;
	std::string modality;
	std::string rows;
	std::string columns;
	std::string pixel_spacing;
	std::string row_pixel_spacing;
	std::string column_pixel_spacing;
	std::string window_width;
	std::string window_center;


private:
	cv::Mat img;

public:

	const std::string &getPatientName();

	void setPatientName(const std::string &patient_name);

	const std::string &getPatientID();

	void setPatientID(const std::string &patient_id);

	const std::string &getPatientDOB();

	void setPatientDOB(const std::string &patient_DOB);

	const std::string &getPatientSex();

	void setPatientSex(const std::string &patient_sex);

	const std::string &getModality();

	void setModality(const std::string &modality);

	const std::string &getRows();

	void setRows(const std::string &rows);

	const std::string &getColumns();

	void setColumns(const std::string &columns);

	const std::string &getPixelSpacing();

	void setPixelSpacing(const std::string &pixel_spacing);

	const std::string &getRowPixelSpacing();

	void setRowPixelSpacing(const std::string row_pixel_spacing);

	const std::string &getColumnPixelSpacing();

	void setColumnPixelSpacing(const std::string column_pixel_spacing);

	const std::string &getWindowWidth();

	void setWindowWidth(const std::string &window_width);

	const std::string &getWindowCenter();

	void setWindowCenter(const std::string &window_center);

	const cv::Mat &getMatImage();

	void setMatImage(const cv::Mat &img);

	void print();
};


#endif // DICOM_H

