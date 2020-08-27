#include "pch.h"
#include "DicomReader.h"
#include "Dicom.h"


vector<string> DicomReader::split(string s, string delimiter) {
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	string token;
	vector<string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

Dicom DicomReader::dicomReader(std::string path)
{
	DcmFileFormat file_format;
	DcmDataset dataSet;
	Dicom saveData;
	//std::string path = "D:\\MFCPrj\\Test\\MRBRAIN.DCM";
	OFCondition status = file_format.loadFile(path.c_str());
	dataSet = DcmDataset(*file_format.getDataset());

	DicomImage *image = new DicomImage(path.c_str());

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

			dataSet.findAndGetOFString(DCM_PatientName, patient_Name);
			dataSet.findAndGetOFString(DCM_PatientID, patient_ID);
			dataSet.findAndGetOFString(DCM_PatientBirthDate, patient_DOB);
			dataSet.findAndGetOFString(DCM_PatientSex, patient_Sex);
			dataSet.findAndGetOFString(DCM_Modality, modality);
			dataSet.findAndGetOFString(DCM_Rows, rows);
			dataSet.findAndGetOFString(DCM_Columns, columns);
			dataSet.findAndGetOFStringArray(DCM_PixelSpacing, pixel_spacing);
			//dataSet.findAndGetOFString(DCM_Rows, rows);


			saveData.setPatientName(patient_Name.c_str());
			saveData.setPatientID(patient_ID.c_str());
			saveData.setPatientDOB(patient_DOB.c_str());
			saveData.setPatientSex(patient_Sex.c_str());
			saveData.setModality(modality.c_str());
			saveData.setRows(rows.c_str());
			saveData.setColumns(columns.c_str());
			//saveData.setPixelSpacing(pixel_spacing.c_str());

			//saveData.print();

			std::string s = pixel_spacing.c_str();
			std::string delim = "\\";

			vector<string> v = split(s, delim);

			saveData.setColumnPixelSpacing(v[0]);
			saveData.setRowPixelSpacing(v[1]);
		}
	}
	return saveData;
}