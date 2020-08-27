#include "pch.h"
#include "Dicom.h"


const std::string &Dicom::getPatientName()
{
	return patient_name;
}

void Dicom::setPatientName(const std::string &patient_name)
{
	Dicom::patient_name = patient_name;
}

const std::string &Dicom::getPatientID()
{
	return patient_id;
}

void Dicom::setPatientID(const std::string &patient_id)
{
	Dicom::patient_id = patient_id;
}

const std::string &Dicom::getPatientDOB()
{
	return patient_DOB;
}

void Dicom::setPatientDOB(const std::string &patient_DOB)
{
	Dicom::patient_DOB = patient_DOB;
}

const std::string &Dicom::getPatientSex()
{
	return patient_sex;
}

void Dicom::setPatientSex(const std::string &patient_sex)
{
	Dicom::patient_sex = patient_sex;
}

const std::string &Dicom::getModality()
{
	return modality;
}

void Dicom::setModality(const std::string &modality)
{
	Dicom::modality = modality;
}

const std::string &Dicom::getRows()
{
	return rows;
}

void Dicom::setRows(const std::string &rows)
{
	Dicom::rows = rows;
}

const std::string &Dicom::getColumns()
{
	return columns;
}

void Dicom::setColumns(const std::string &columns)
{
	Dicom::columns = columns;
}

const std::string &Dicom::getPixelSpacing()
{
	return pixel_spacing;
}

void Dicom::setPixelSpacing(const std::string &pixel_spacing)
{
	Dicom::pixel_spacing = pixel_spacing;
}

const std::string &Dicom::getRowPixelSpacing()
{
	return row_pixel_spacing;
}

void Dicom::setRowPixelSpacing(const std::string row_pixel_spacing)
{
	Dicom::row_pixel_spacing = row_pixel_spacing;
}

const std::string &Dicom::getColumnPixelSpacing()
{
	return column_pixel_spacing;
}

void Dicom::setColumnPixelSpacing(const std::string column_pixel_spacing)
{
	Dicom::column_pixel_spacing = column_pixel_spacing;
}

const std::string &Dicom::getWindowWidth()
{
	return window_width;
}

void Dicom::setWindowWidth(const std::string &window_width)
{
	Dicom::window_width = window_width;
}

const std::string &Dicom::getWindowCenter()
{
	return window_center;
}

void Dicom::setWindowCenter(const std::string &window_center)
{
	Dicom::window_center = window_center;
}

const cv::Mat &Dicom::getMatImage()
{
	return img;
}

void Dicom::setMatImage(const cv::Mat &img)
{
	Dicom::img = img;
}

void Dicom::print()
{
	std::cout << "Name: " << patient_name << " ID: " << patient_id << " DOB: " << patient_DOB << " Sex: " << patient_sex << " Modality: " << modality
		<< " rows: " << rows << " column: " << columns << " row spacing: " << row_pixel_spacing << " column spacing: " << column_pixel_spacing
		<< " window width: " << window_width << " window center: " << window_center << std::endl;
}