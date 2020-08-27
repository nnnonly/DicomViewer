#include "pch.h"


#include "DicomViewer.h"
#include "Dicom.h"
#include "DicomReader.h"

std::string DicomViewer::loadPath(CFileDialog &dlg)
{
	CString filePath = dlg.GetPathName();
	std::string sPath = filePath.GetString();
	return sPath;
}

void DicomViewer::loadImage(std::string path)
{

}
