
// LoadPictureDlg.h : header file
//

#pragma once
#include "CoreInclude.h"

// CLoadPictureDlg dialog
class CLoadPictureDlg : public CDialogEx
{
// Construction
public:
	CLoadPictureDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADPICTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	void updateView();
	void loadImage(cv::Mat img);
	cv::Mat fitImage(const cv::Mat &img);

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedDetectMarker();
	afx_msg void OnBnClickedSave();

	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeShowW();
	afx_msg void OnEnChangeShowC();
	

	CString m_PatientName;
	CString m_PatientID;
	CString m_Birth;
	CString m_Sex;
	CString m_Modality;
	CString m_Row;
	CString m_Column;
	CString m_ColumnPS;
	CString m_RowPS;

	CSliderCtrl m_sld_width;
	CEdit m_ed_width;
	CSliderCtrl m_sld_center;
	CEdit m_ed_center;
	
	afx_msg void OnBnClickedDebug();
};
