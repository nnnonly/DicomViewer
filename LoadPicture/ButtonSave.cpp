// ButtonSave.cpp : implementation file
//

#include "pch.h"
#include "LoadPicture.h"
#include "ButtonSave.h"
#include "afxdialogex.h"


// ButtonSave dialog

IMPLEMENT_DYNAMIC(ButtonSave, CDialogEx)

ButtonSave::ButtonSave(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_DICOM_VIEWER, pParent)
{

}

ButtonSave::~ButtonSave()
{
}

void ButtonSave::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ButtonSave, CDialogEx)
	ON_BN_CLICKED(ID_SAVE, &ButtonSave::OnBnClickedSave)
END_MESSAGE_MAP()


// ButtonSave message handlers


void ButtonSave::OnBnClickedSave()
{
	// TODO: Add your control notification handler code here

}
