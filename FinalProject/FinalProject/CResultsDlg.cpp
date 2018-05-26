#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "CResultsDlg.h"

#include "afxdialogex.h"

CResultsDlg::CResultsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RESULT_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}