
// FinalProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FinalProject.h"
#include "FinalProjectDlg.h"
#include "afxdialogex.h"
#include "fstream"
#include "iostream"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFinalProjectDlg dialog



CFinalProjectDlg::CFinalProjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINALPROJECT_DIALOG, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

/*
	Controls of screen elements (EditControl, StaticText, etc...)

 */
void CFinalProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_FilePath);
	DDX_Control(pDX, IDC_COMBO1, m_SelectionCombo);
	DDX_Control(pDX, IDC_COMBO2, m_CrossComboBox);
	DDX_Control(pDX, IDC_COMBO3, m_MutationComboBox);
	DDX_Control(pDX, IDC_EDIT3, m_GenerationsNum);
	DDX_Control(pDX, IDC_EDIT4, m_ElitismNum);
	DDX_Control(pDX, IDC_EDIT5, m_IterationFix);
	DDX_Control(pDX, IDC_EDIT6, m_Epsilon);
	DDX_Control(pDX, IDC_EDIT8, m_MigrationInKB);
	DDX_Control(pDX, IDC_EDIT7, m_MigrationInPercent);
	DDX_Control(pDX, IDC_EDIT2, m_RatePercent);
}

/*
	Decalares the event handlers for various interactions with the GUI
 */
BEGIN_MESSAGE_MAP(CFinalProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFinalProjectDlg::OnBrowseClick)
	ON_BN_CLICKED(IDC_RADIO1, &CFinalProjectDlg::OnMigrationInKB)
	ON_BN_CLICKED(IDC_RADIO2, &CFinalProjectDlg::OnMigrationInPercent)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CFinalProjectDlg::OnCbSelection)
	ON_EN_CHANGE(IDC_EDIT2, &CFinalProjectDlg::OnRatePercentChange)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CFinalProjectDlg::OnCbnCrossover)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CFinalProjectDlg::OnCbnMutation)
	ON_BN_CLICKED(IDOK, &CFinalProjectDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT7, &CFinalProjectDlg::OnFilePercentChange)
END_MESSAGE_MAP()


// CFinalProjectDlg message handlers

BOOL CFinalProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// Selection ComboBox initialization
	m_SelectionCombo.AddString(CA2W("Roulette wheel selection"));
	m_SelectionCombo.AddString(CA2W("Linear rank-based selection"));
	m_SelectionCombo.AddString(CA2W("Tournament selection"));
	// Cross-over ComboBox initialization
	m_CrossComboBox.AddString(CA2W("One-point crossover"));
	m_CrossComboBox.AddString(CA2W("Two-point crossover"));
	m_CrossComboBox.AddString(CA2W("Uniform crossover"));
	// Mutation ComboBox initialization
	m_MutationComboBox.AddString(CA2W("Single-point mutation"));
	m_MutationComboBox.AddString(CA2W("Uniform mutation"));
	// Percentage edit control
	m_RatePercent.SetWindowTextW(CA2W("%"));
	// Radio buttons
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFinalProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFinalProjectDlg::OnPaint()
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
HCURSOR CFinalProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFinalProjectDlg::OnBrowseClick()
{
	// Creates 'Browse-Files' dialog which consists of text files
	CFileDialog fileDlg(TRUE, CA2W("txt"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, CA2W("Text Files (*.txt)|*.txt|||"), this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString PathName = fileDlg.GetPathName();
		m_FilePath.SetWindowTextW(PathName);
	}
}


void CFinalProjectDlg::OnMigrationInKB()
{
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(TRUE);
}


void CFinalProjectDlg::OnMigrationInPercent()
{
	m_MigrationInPercent.EnableWindow(TRUE);
	m_MigrationInKB.EnableWindow(FALSE);
}


void CFinalProjectDlg::OnCbSelection()
{
	// TODO: Add your control notification handler code here
}

void CFinalProjectDlg::OnCbnCrossover()
{
	// TODO: Add your control notification handler code here
}

void CFinalProjectDlg::OnCbnMutation()
{
	// TODO: Add your control notification handler code here
}


void CFinalProjectDlg::OnRatePercentChange()
{
	UpdateData(TRUE);
	CString perCS;
	CStringA perCSA;
	m_RatePercent.GetWindowTextW(perCS);
	perCSA = perCS;
	if (perCS.GetLength() != 0) {

		int percent = atoi(perCSA);
		if (percent > 100 || percent < 0) {
			MessageBox(CA2W("% is 0~100\n Please insert valid value..."), CA2W("Percentage Correctness"), MB_ICONERROR | MB_OK);
		}
	}
	else if (perCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
	
}

void CFinalProjectDlg::OnFilePercentChange()
{
	UpdateData(TRUE);
	CString perCS;
	CStringA perCSA;
	m_MigrationInPercent.GetWindowTextW(perCS);
	perCSA = perCS;
	if (perCS.GetLength() != 0) {

		int percent = atoi(perCSA);
		if (percent > 100 || percent < 0) {
			MessageBox(CA2W("% is 0~100\n Please insert valid value..."), CA2W("Percentage Correctness"), MB_ICONERROR | MB_OK);
		}
	}
	else if (perCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnBnClickedOk()
{
	ifstream input;
	CString s;
	char line;
	m_FilePath.GetWindowTextW(s);
	input.open(s);
	if (!input) {
		MessageBox(CA2W("Error loading text file"), NULL, MB_ICONERROR | MB_OK);
	}
	while (!input.eof()) {	// Start to process the text of the input
		
	}
	CDialogEx::OnOK();
}



