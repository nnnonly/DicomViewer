
// LoadPictureDlg.h : header file
//

#pragma once


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

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedDetectMarker();
};
