#include "pch.h"
#include "WindowController.h"


std::string WindowController::loadPath(CFileDialog& dlg)
{
	CString filePath = dlg.GetPathName();
	std::string sPath = filePath.GetString();
	return sPath;
}


std::vector<std::string> WindowController::split(std::string s, std::string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}
	res.push_back(s.substr(pos_start));
	return res;
}


int WindowController::loadInforImage(std::string path, cv::Mat &imag, Dicom &saveData)
{
	DcmFileFormat file_format;
	DcmDataset dataSet;
	OFCondition status = file_format.loadFile(path.c_str());
	dataSet = DcmDataset(*file_format.getDataset());

	DicomImage *image = new DicomImage(path.c_str());
	image->setWindow(1048, 4096);

	if (image != NULL)
	{
		if (image->getStatus() == EIS_Normal)
		{

			OFString patient_Name;
			OFString patient_ID;
			OFString patient_DOB;
			OFString patient_Sex;
			OFString modality;
			OFString rows;
			OFString columns;
			OFString pixel_spacing;
			OFString pixel_row;
			OFString pixel_col;
			OFString window_width;
			OFString window_center;


			dataSet.findAndGetOFString(DCM_PatientName, patient_Name);
			dataSet.findAndGetOFString(DCM_PatientID, patient_ID);
			dataSet.findAndGetOFString(DCM_PatientBirthDate, patient_DOB);
			dataSet.findAndGetOFString(DCM_PatientSex, patient_Sex);
			dataSet.findAndGetOFString(DCM_Modality, modality);
			dataSet.findAndGetOFString(DCM_Rows, rows);
			dataSet.findAndGetOFString(DCM_Columns, columns);
			dataSet.findAndGetOFStringArray(DCM_PixelSpacing, pixel_spacing);
			dataSet.findAndGetOFString(DCM_WindowWidth, window_width);
			dataSet.findAndGetOFString(DCM_WindowCenter, window_center);
			//dataSet.findAndGetOFString(DCM_Rows, rows);

			cv::Mat img(int(image->getWidth()), int(image->getHeight()), CV_8U, (uchar*)image->getOutputData(8));
			/*cv::normalize(img, img, 0, 255, cv::NORM_MINMAX);
			img.convertTo(img, CV_8UC1);*/
			
			saveData.setPatientName(patient_Name.c_str());
			saveData.setPatientID(patient_ID.c_str());
			saveData.setPatientDOB(patient_DOB.c_str());
			saveData.setPatientSex(patient_Sex.c_str());
			saveData.setModality(modality.c_str());
			saveData.setRows(rows.c_str());
			saveData.setColumns(columns.c_str());

			

			//saveData.print();

			std::string s = pixel_spacing.c_str();
			std::string delim = "\\";

			std::vector<std::string> v = split(s, delim);

			saveData.setColumnPixelSpacing(v[0]);
			saveData.setRowPixelSpacing(v[1]);
			saveData.setWindowWidth(window_width.c_str());
			saveData.setWindowCenter(window_center.c_str());

			imag = img.clone();
		}
		else
		{
			std::cerr << "Cannot load image";
			return 100;
		}
	}
	delete image;
	return 0;
}