// OpenButton.cpp : implementation file
//

#include "pch.h"
#include "LoadPicture.h"
#include "OpenButton.h"
#include "afxdialogex.h"


// OpenButton dialog

IMPLEMENT_DYNAMIC(OpenButton, CDialogEx)

OpenButton::OpenButton(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_DICOM_VIEWER, pParent)
{

}

OpenButton::~OpenButton()
{
}

void OpenButton::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(OpenButton, CDialogEx)
END_MESSAGE_MAP()


// OpenButton message handlers
