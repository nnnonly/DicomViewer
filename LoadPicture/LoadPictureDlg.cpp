
// LoadPictureDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LoadPicture.h"
#include "LoadPictureDlg.h"
#include "afxdialogex.h"

#include "opencv2/opencv.hpp"
#include <string>

#include "dcmtk/dcmdata/dctk.h"
#include "dcmtk/dcmimgle/dcmimage.h"

using namespace cv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLoadPictureDlg dialog



CLoadPictureDlg::CLoadPictureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADPICTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLoadPictureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &CLoadPictureDlg::OnBnClickedOpen)
	ON_BN_CLICKED(ID_SAVE, &CLoadPictureDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_DETECT_MARKER, &CLoadPictureDlg::OnBnClickedDetectMarker)
END_MESSAGE_MAP()


// CLoadPictureDlg message handlers

BOOL CLoadPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLoadPictureDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLoadPictureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CLoadPictureDlg::OnBnClickedOpen()
{
	 //TODO: Add your control notification handler code here
	CFileDialog dlg(true, NULL, _T("*.jpg"), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp ;*.jpg)|*.bmp; *.jpg| DICOM files (*.dcm)|*.dcm; *.DCM; *.Dcm |ALL Files (*.*) |*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("open Image");

	if (dlg.DoModal() != IDOK)
	{
		//MessageBox(_T("Load img error!"));
		return;
	}


	CString filePath = dlg.GetPathName();

	CT2CA pszConvertedAnsiString(filePath);

	string sPath(pszConvertedAnsiString);

	DicomImage *image = new DicomImage(sPath.c_str());
	if (image != NULL)
	{
		if (image->getStatus() == EIS_Normal)
		{
			if (image->isMonochrome())
			{
				image->setMinMaxWindow();
				Uint8 *pixelData = (Uint8 *)(image->getOutputData(8 /* bits */));
				if (pixelData != NULL)
				{
					/* do something useful with the pixel data */
				}
			}
		}
		else
			cerr << "Error: cannot load DICOM image (" << DicomImage::getString(image->getStatus()) << ")" << endl;
	}
	//delete image;
	//Mat img = imread(status);
	Mat img;
	unsigned int nRows = image->getHeight();
	unsigned int nCols = image->getWidth();
	unsigned int nImgs = image->getFrameCount();

	vector<Mat> slices(nImgs);

	for (int k = 0; k < nImgs; k++)
	{
		Uint8 * pixelData = (Uint8*)(image->getOutputData(8 /* bits */, k /* slice */));

		slices[k] = Mat(nRows, nCols, CV_8U, pixelData).clone();
	}

	merge(slices, img);


	if (img.empty())
	{
		MessageBox(_T("Load img error!"));
		return;
	}
	
	CRect rect;
	GetDlgItem(ID_IMAGE)->GetClientRect(&rect);

	cv::resize(img, img, cv::Size(rect.Width(), rect.Height()));

	switch (img.channels())
	{
	case 1:
		cv::cvtColor(img, img, CV_GRAY2BGRA); //gray
		break;

	case 2:
		cv::cvtColor(img, img, CV_BGR2BGRA);
		break;

	default:
		break;
	}

	//tinh xem co bao nhieu byte trong 1 pixel
	int pixelBytes = img.channels() * (img.depth() + 1);
	BITMAPINFO bitInfor;

	bitInfor.bmiHeader.biBitCount = 8 * pixelBytes;
	bitInfor.bmiHeader.biWidth = img.cols;
	bitInfor.bmiHeader.biHeight = -img.rows;
	bitInfor.bmiHeader.biPlanes = 1;
	bitInfor.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfor.bmiHeader.biCompression = BI_RGB;
	bitInfor.bmiHeader.biClrImportant = 0;
	bitInfor.bmiHeader.biClrUsed = 0;
	bitInfor.bmiHeader.biSizeImage = 0;
	bitInfor.bmiHeader.biXPelsPerMeter = 0;
	bitInfor.bmiHeader.biYPelsPerMeter = 0;

	CDC *pDC = GetDlgItem(ID_IMAGE)->GetDC();

	::StretchDIBits(
		pDC->GetSafeHdc(),
		0, 0, rect.Width(), rect.Height(),
		0, 0, img.cols, img.rows,
		img.data,
		&bitInfor,
		DIB_RGB_COLORS,
		SRCCOPY
	);
	ReleaseDC(pDC);

}



void CLoadPictureDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here

	
}


void CLoadPictureDlg::OnBnClickedDetectMarker()
{
	// TODO: Add your control notification handler code here
	
}
