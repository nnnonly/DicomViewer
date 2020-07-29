#pragma once


// ButtonSave dialog

class ButtonSave : public CDialogEx
{
	DECLARE_DYNAMIC(ButtonSave)

public:
	ButtonSave(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ButtonSave();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_DICOM_VIEWER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSave();
};
