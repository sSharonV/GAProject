#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "GA_Evolution.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

class GA_Evolution;
class GA_Migration;

// CResultDlg dialog

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)

public:
	CResultDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CResultDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SECOND };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCancelClick();
	afx_msg void OnSaveClick();
private:
	bool fileExists(string fileName);
};
