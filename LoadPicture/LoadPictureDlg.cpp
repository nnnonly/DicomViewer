
// LoadPictureDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LoadPicture.h"
#include "LoadPictureDlg.h"
#include "afxdialogex.h"

#include "WindowController.h"
#include "DisplayLUT.h"
#include "AppDocument.h"
#include "DetectMarker.h"

using namespace cv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CLoadPictureDlg dialog

std::string over_path;


CLoadPictureDlg::CLoadPictureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOADPICTURE_DIALOG, pParent)
	, m_PatientName(_T(""))
	, m_PatientID(_T(""))
	, m_Birth(_T(""))
	, m_Sex(_T(""))
	, m_Modality(_T(""))
	, m_Row(_T(""))
	, m_Column(_T(""))
	, m_ColumnPS(_T(""))
	, m_RowPS(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLoadPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_SHOW_NAME, m_PatientName);
	DDX_Text(pDX, ID_SHOW_ID, m_PatientID);
	DDX_Text(pDX, ID_SHOW_BIRTH_DATE, m_Birth);
	DDX_Text(pDX, ID_SHOW_SEX, m_Sex);
	DDX_Text(pDX, ID_SHOW_MODALITY, m_Modality);
	DDX_Text(pDX, ID_SHOW_ROW, m_Row);
	DDX_Text(pDX, ID_SHOW_COLUMN, m_Column);
	DDX_Text(pDX, ID_SHOW_CS, m_ColumnPS);
	DDX_Text(pDX, ID_SHOW_RS, m_RowPS);
	DDX_Control(pDX, ID_SLIDER_01, m_sld_width);
	DDX_Control(pDX, ID_SHOW_WW, m_ed_width);
	DDX_Control(pDX, ID_SLIDER_02, m_sld_center);
	DDX_Control(pDX, ID_SHOW_WC, m_ed_center);
}

BEGIN_MESSAGE_MAP(CLoadPictureDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_OPEN, &CLoadPictureDlg::OnBnClickedOpen)
	ON_BN_CLICKED(ID_DETECT_MARKER, &CLoadPictureDlg::OnBnClickedDetectMarker)
	ON_BN_CLICKED(ID_SAVE, &CLoadPictureDlg::OnBnClickedSave)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(ID_SHOW_WW, &CLoadPictureDlg::OnEnChangeShowW)
	ON_EN_CHANGE(ID_SHOW_WC, &CLoadPictureDlg::OnEnChangeShowC)
	ON_BN_CLICKED(ID_DEBUG, &CLoadPictureDlg::OnBnClickedDebug)
END_MESSAGE_MAP()


// CLoadPictureDlg message handlers
void CLoadPictureDlg::updateView() 
{
	AppDocument* updateApp = AppDocument::getInstance();
	if (updateApp->getMatImage().empty()) {
		return;
	}
	
	updateApp->getWidth();
	updateApp->getCenter();

	cv::Mat output;	

	DisplayLUT::loadPixel(std::atoi(updateApp->getWidth().c_str()), std::atoi(updateApp->getCenter().c_str()), updateApp->getMatImage(), output);
	cv::cvtColor(output, output, CV_GRAY2BGR);

	if (updateApp->getPointPlus().size() != 0 && updateApp->getPointMulti().size() != 0)
	{
		DetectMarker::drawMarkerPlus(output, updateApp->getPointPlus());
		DetectMarker::drawMarkerMulti(output, updateApp->getPointMulti());
	}

	cv::Mat after = fitImage(output);

	loadImage(after);
	
}

void CLoadPictureDlg::loadImage(cv::Mat img)
{
	CRect rect;
	GetDlgItem(ID_IMAGE)->GetClientRect(&rect);

	cv::resize(img, img, cv::Size(rect.Width(), rect.Height()));

	switch (img.channels())
	{
	case 1:
		cv::cvtColor(img, img, CV_GRAY2BGRA); //gray
		break;

	case 3:
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


cv::Mat CLoadPictureDlg::fitImage(const cv::Mat &img)
{
	int width = img.cols,
		height = img.rows;
	
	cv::Mat image_frame = cv::Mat::ones(360, 600, img.type());
	image_frame.mul(127);
	cv::Mat img_resize;
	
	if ((width >= 360) && (height >= 360))
	{
		cv::resize(img, img_resize, cv::Size(360, 360));
	}
	else if ((width >= 360) && (height < 360))
	{
		cv::resize(img, img_resize, cv::Size(height, height));
	}
	else if ((width < 360) && (height >= width))
	{
		cv::resize(img, img_resize, cv::Size(width, width));
	}
	else if ((width < 360) && (height < 360))
	{
		if (width >= height)
		{
			cv::resize(img, img_resize, cv::Size(width, width));
		}
		cv::resize(img, img_resize, cv::Size(height, height));
	}
	
	
	cv::Mat destRoi;
	destRoi = image_frame(cv::Rect(120, 0, img_resize.cols, img_resize.rows));
	img_resize.copyTo(destRoi);
	return image_frame;
}



BOOL CLoadPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_sld_width.SetRange(0, 4095);
	m_sld_width.SetPos(0);

	int iwPos = m_sld_width.GetPos();
	CString swPos;
	swPos.Format(_T("%d"), iwPos);
	m_ed_width.SetWindowText(swPos);


	//cv::Mat;
	m_sld_center.SetRange(-1000, 3095);
	m_sld_center.SetPos(0);

	int icPos = m_sld_center.GetPos();
	CString scPos;
	scPos.Format(_T("%d"), icPos);
	m_ed_center.SetWindowText(scPos);
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

	CFileDialog dlg(true, NULL, _T("*.dcm"), OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("DICOM files (*.dcm)|*.dcm; *.DCM; *.Dcm| ALL Files (*.*) |*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("open Image");

	
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	std::string path = WindowController::loadPath(dlg);

	over_path = path;
	Dicom data;
	cv::Mat img;
	cv::Mat dicomImage;

	WindowController::loadInforImage(path, img, data);

	AppDocument* appDoc = AppDocument::getInstance();
	appDoc->setDicomPath(path);
	appDoc->getDicomPath();
	appDoc->setMatImage(img);
	appDoc->setRowPS(data.getRowPixelSpacing().c_str());
	appDoc->setColPS(data.getColumnPixelSpacing().c_str());
	appDoc->setWidth(data.getWindowWidth().c_str());
	appDoc->setCenter(data.getWindowCenter().c_str());

	double roww = std::atof(appDoc->getRowPS().c_str());
	double coll = std::atof(appDoc->getColPS().c_str());

	cv::Mat output;
	DisplayLUT::loadPixel(std::atoi(data.getWindowWidth().c_str()), std::atoi(data.getWindowCenter().c_str()), img, output);
	loadImage(output);

	UpdateData(TRUE);

	CWnd *label_name = GetDlgItem(ID_SHOW_NAME);
	label_name->SetWindowText(data.getPatientName().c_str());

	CWnd *label_id = GetDlgItem(ID_SHOW_ID);
	label_id->SetWindowText(data.getPatientID().c_str());

	CWnd *label_dob = GetDlgItem(ID_SHOW_BIRTH_DATE);
	label_dob->SetWindowText(data.getPatientDOB().c_str());

	CWnd *label_sex = GetDlgItem(ID_SHOW_SEX);
	label_sex->SetWindowText(data.getPatientSex().c_str());

	CWnd *label_modality = GetDlgItem(ID_SHOW_MODALITY);
	label_modality->SetWindowText(data.getModality().c_str());

	CWnd *label_row = GetDlgItem(ID_SHOW_ROW);
	label_row->SetWindowText(data.getRows().c_str());

	CWnd *label_column = GetDlgItem(ID_SHOW_COLUMN);
	label_column->SetWindowText(data.getColumns().c_str());

	CWnd *label_cps = GetDlgItem(ID_SHOW_CS);
	label_cps->SetWindowText(data.getColumnPixelSpacing().c_str());

	CWnd *label_rps = GetDlgItem(ID_SHOW_RS);
	label_rps->SetWindowText(data.getRowPixelSpacing().c_str());

	CWnd *label_ww = GetDlgItem(ID_SHOW_WW);
	label_ww->SetWindowText(data.getWindowWidth().c_str());
	

	CWnd *label_wc = GetDlgItem(ID_SHOW_WC);
	label_wc->SetWindowText(data.getWindowCenter().c_str());
	UpdateData(TRUE);
}

void CLoadPictureDlg::OnBnClickedDetectMarker()
{
	// TODO: Add your control notification handler code here
	AppDocument* appDoc = AppDocument::getInstance();
	cv::Mat cloneImg = appDoc->getMatImage();
	cv::Mat detectImg;
	
	DisplayLUT::loadPixel(std::atoi(appDoc->getWidth().c_str()), std::atoi(appDoc->getCenter().c_str()), cloneImg, detectImg);
	cv::Mat outputDtcImg = detectImg.clone();

	std::vector<cv::Point2f> centerPointPlus;
	std::vector<cv::Point2f> centerPointMulti;

	DetectMarker::preProcessing(detectImg);
	cv::Mat maskPlus;
	DetectMarker::GeneratePlusMask(maskPlus, std::atof(appDoc->getRowPS().c_str()), std::atof(appDoc->getColPS().c_str()), 9, 9);

	cv::Mat maskMulti;
	DetectMarker::GenerateMultiMask(maskMulti, std::atof(appDoc->getRowPS().c_str()), std::atof(appDoc->getColPS().c_str()), 9, 9);

	DetectMarker::featureExtraction(detectImg, maskPlus, maskMulti, centerPointPlus, centerPointMulti);

	std::vector<cv::Point2f> drawPlus = DetectMarker::postProcessingPlus(detectImg, centerPointPlus);
	appDoc->setPointPlus(drawPlus);

	std::vector<cv::Point2f> drawMulti = DetectMarker::postProcessingMulti(detectImg, centerPointMulti);
	appDoc->setPointMulti(drawMulti);


	updateView();
	cv::waitKey(0);
	
}

void CLoadPictureDlg::OnBnClickedSave()
{
	// TODO: Add your control notification handler code
	UpdateData();
	DcmFileFormat file_format;
	DcmDataset dataSet;

	OFCondition status = file_format.loadFile(over_path.c_str());
	dataSet = DcmDataset(*file_format.getDataset());

	if (status.good())
	{
		dataSet.putAndInsertString(DCM_PatientName, m_PatientName, true);
		dataSet.putAndInsertString(DCM_PatientID, m_PatientID, true);
		dataSet.putAndInsertString(DCM_PatientBirthDate, m_Birth, true);
		dataSet.putAndInsertString(DCM_PatientSex, m_Sex, true);
		dataSet.putAndInsertString(DCM_Modality, m_Modality, true);
		dataSet.putAndInsertString(DCM_Rows, m_Row, true);
		dataSet.putAndInsertString(DCM_Columns, m_Column, true);
		dataSet.putAndInsertString(DCM_PixelSpacing, m_ColumnPS + "\\" + m_RowPS, true);

		OFCondition stt = dataSet.saveFile("testing.dcm");
	}
	else
		cerr << "Error: cannot read DICOM file (" << status.text() << ")" << endl;
		
}

void CLoadPictureDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{

	// TODO: Add your message handler code here and/or call default
	if (ID_SLIDER_01 == pScrollBar->GetDlgCtrlID())
	{
		int iwPos = m_sld_width.GetPos();
		CString swPos;
		swPos.Format(_T("%d"), iwPos);
		m_ed_width.SetWindowText(swPos);
	}

	if (ID_SLIDER_02 == pScrollBar->GetDlgCtrlID())
	{
		int icPos = m_sld_center.GetPos();
		CString scPos;
		scPos.Format(_T("%d"), icPos);
		m_ed_center.SetWindowText(scPos);
	}

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CLoadPictureDlg::OnEnChangeShowW()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	
	CString swPos;
	m_ed_width.GetWindowText(swPos);
	int iwPos = _ttoi(swPos);
	m_sld_width.SetPos(iwPos);
	AppDocument* updateAppWidth = AppDocument::getInstance();
	std::string stdswPos = swPos;
	updateAppWidth->setWidth(stdswPos);
	updateView();
}


void CLoadPictureDlg::OnEnChangeShowC()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here

	CString scPos; //sPos
	m_ed_center.GetWindowText(scPos);
	int icPos = _ttoi(scPos);
	m_sld_center.SetPos(icPos);
	AppDocument* updateAppCenter = AppDocument::getInstance();
	std::string stdscPos = scPos;
	updateAppCenter->setCenter(stdscPos);
	updateView();
}




void CLoadPictureDlg::OnBnClickedDebug()
{
	// TODO: Add your control notification handler code here
}
