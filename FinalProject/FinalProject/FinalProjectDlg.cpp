
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
#define new1 DEBUG_NEW
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
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
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
	DDX_Control(pDX, IDC_EDIT10, m_SelError);
	DDX_Control(pDX, IDC_EDIT11, m_CrosError);
	DDX_Control(pDX, IDC_EDIT12, m_MutError);
	DDX_Control(pDX, IDC_EDIT13, m_RateError);
	DDX_Control(pDX, IDC_EDIT14, m_GenError);
	DDX_Control(pDX, IDC_EDIT15, m_ElitError);
	DDX_Control(pDX, IDC_EDIT16, m_FixError);
	DDX_Control(pDX, IDC_EDIT17, m_EpsError);
	DDX_Control(pDX, IDC_EDIT18, m_SizeError);
	DDX_Control(pDX, IDC_COMBO4, m_DiffrentMeasure);
	DDX_Control(pDX, IDC_COMBO5, m_EpsilonMeasure);
	DDX_Control(pDX, IDC_EDIT9, m_PopulationSize);
	DDX_Control(pDX, IDC_EDIT19, m_PopError);
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
	ON_EN_CHANGE(IDC_EDIT3, &CFinalProjectDlg::OnGenChange)
	ON_EN_CHANGE(IDC_EDIT4, &CFinalProjectDlg::OnElitChange)
	ON_EN_CHANGE(IDC_EDIT5, &CFinalProjectDlg::OnIterFixChange)
	ON_EN_CHANGE(IDC_EDIT6, &CFinalProjectDlg::OnEpsilonChange)
	ON_EN_CHANGE(IDC_EDIT8, &CFinalProjectDlg::OnSizeKBChange)
	ON_BN_CLICKED(IDC_BUTTON2, &CFinalProjectDlg::OnReset)
	ON_BN_CLICKED(IDCANCEL, &CFinalProjectDlg::OnExitClick)
	ON_EN_CHANGE(IDC_EDIT9, &CFinalProjectDlg::OnPopulationSizeChange)
	ON_EN_CHANGE(IDC_EDIT20, &CFinalProjectDlg::OnExpectedValChange)
	ON_EN_CHANGE(IDC_EDIT21, &CFinalProjectDlg::OnMutationRateChange)
	ON_EN_CHANGE(IDC_EDIT24, &CFinalProjectDlg::OnTimeOutChange)
	ON_BN_CLICKED(IDC_BUTTON3, &CFinalProjectDlg::OnBnClickedButton3)
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
	braudeLogo = ((CStatic*)GetDlgItem(IDC_LOGOB));
	//m_resultDlg = NULL;
	read_input = true;
	// Selection ComboBox initialization
	m_SelectionCombo.AddString(CA2W("Roulette wheel selection"));
	m_SelectionCombo.AddString(CA2W("Linear rank-based selection"));
	m_SelectionCombo.AddString(CA2W("Tournament selection"));
	m_SelectionCombo.SetCurSel(0);
	// Cross-over ComboBox initialization
	m_CrossComboBox.AddString(CA2W("One-point crossover"));
	m_CrossComboBox.AddString(CA2W("Two-point crossover"));
	m_CrossComboBox.AddString(CA2W("Uniform crossover"));
	m_CrossComboBox.SetCurSel(0);
	// Mutation ComboBox initialization
	m_MutationComboBox.AddString(CA2W("Single-point mutation"));
	m_MutationComboBox.AddString(CA2W("Uniform mutation"));
	m_MutationComboBox.SetCurSel(0);
	// Defines diffrent measures for defining number of bytes by the user
	m_DiffrentMeasure.AddString(CA2W("Kilo"));
	m_DiffrentMeasure.AddString(CA2W("Mega"));
	m_DiffrentMeasure.AddString(CA2W("Giga"));
	m_DiffrentMeasure.SetCurSel(0);
	// Defines diffrent measures for epsilon
	m_EpsilonMeasure.AddString(CA2W("Kilo"));
	m_EpsilonMeasure.AddString(CA2W("Mega"));
	m_EpsilonMeasure.AddString(CA2W("Giga"));
	m_EpsilonMeasure.SetCurSel(0);
	// Radio buttons
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(FALSE);
	m_DiffrentMeasure.EnableWindow(FALSE);
	// Init error editors
	m_SelError.SetWindowTextW(CA2W(""));
	m_CrosError.SetWindowTextW(CA2W(""));
	m_MutError.SetWindowTextW(CA2W(""));
	m_RateError.SetWindowTextW(CA2W(""));
	m_GenError.SetWindowTextW(CA2W(""));
	m_ElitError.SetWindowTextW(CA2W(""));
	m_FixError.SetWindowTextW(CA2W(""));
	m_EpsError.SetWindowTextW(CA2W(""));
	m_SizeError.SetWindowTextW(CA2W(""));

	EnableFields(false);

	/*------------------------Input Examples - Size in KB---------------------------*/

	true_KB = true;
	m_PopulationSize.SetWindowTextW(CA2W("10"));
	m_RatePercent.SetWindowTextW(CA2W("15"));
	m_GenerationsNum.SetWindowTextW(CA2W("10"));
	m_ElitismNum.SetWindowTextW(CA2W("2"));
	m_IterationFix.SetWindowTextW(CA2W("3"));
	m_Epsilon.SetWindowTextW(CA2W("1"));
	m_MigrationInKB.SetWindowTextW(CA2W("500"));
	GetDlgItem(IDC_EDIT24)->SetWindowTextW(CA2W("5"));
	GetDlgItem(IDC_EDIT21)->SetWindowTextW(CA2W("15"));

	// Loading the braude logo...
	viewImage.Load(_T("res/Capture.JPG"));
	viewBitmap.Attach(viewImage.Detach());
	braudeLogo->SetBitmap((HBITMAP)viewBitmap);
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

/***********************************************************************************************************/
/*												GUI Handlers											   */
/***********************************************************************************************************/
void CFinalProjectDlg::OnBrowseClick()
{
	// Creates 'Browse-Files' dialog which consists of ".CSV" files
	CFileDialog fileDlg(TRUE, CA2W("csv"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, CA2W("CSV Files (*.csv)|*.csv|||"), this);
	if (fileDlg.DoModal() == IDOK)
	{
		CString PathName = fileDlg.GetPathName();
		if (PathName.IsEmpty()) {
			MessageBox(CA2W("Please select CSV file from the file explorer to procced..."), NULL, MB_ICONERROR | MB_OK);
			return;
		}
		m_FilePath.SetWindowTextW(PathName);
		EnableFields(true);
		m_MigrationInKB.EnableWindow(TRUE);
		m_DiffrentMeasure.EnableWindow(TRUE);
		m_MigrationInPercent.EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
		true_KB = true;
	}
}

void CFinalProjectDlg::OnMigrationInKB()
{
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(TRUE);
	m_DiffrentMeasure.EnableWindow(TRUE);
	true_KB = true;
}

void CFinalProjectDlg::OnMigrationInPercent()
{
	m_MigrationInPercent.EnableWindow(TRUE);
	m_MigrationInKB.EnableWindow(FALSE);
	m_DiffrentMeasure.EnableWindow(FALSE);
	true_KB = false;
}

void CFinalProjectDlg::OnCbSelection()
{
	m_SelError.SetWindowTextW(CA2W(""));
	int sel = m_SelectionCombo.GetCurSel();
	// Update selection method
	if (sel == 1) {
		GetDlgItem(IDC_EDIT20)->EnableWindow(TRUE);
	}
	else {
		GetDlgItem(IDC_EDIT20)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT20)->SetWindowTextW(CA2W(""));
	}
		
	
}

void CFinalProjectDlg::OnCbnCrossover()
{
	m_CrosError.SetWindowTextW(CA2W(""));
}

void CFinalProjectDlg::OnCbnMutation()
{
	m_MutError.SetWindowTextW(CA2W(""));
}

void CFinalProjectDlg::OnMutationRateChange()
{
	CString mutCS;
	CStringA mutCSA;
	GetDlgItem(IDC_EDIT23)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT21)->GetWindowTextW(mutCS);
	mutCSA = mutCS;
	if (mutCS.GetLength() != 0) {
		string mutS((CT2A)mutCS);
		long double size = stold(mutS);
		if (size < 0 || size > 100) {
			MessageBox(CA2W("Mutation Rate can be in interval of [0,100]"), NULL, MB_ICONERROR | MB_OK);
			GetDlgItem(IDC_EDIT20)->SetWindowTextW(CA2W(""));
		}
	}
	else if (mutCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnExpectedValChange()
{
	CString exCS; 
	CStringA exCSA;
	GetDlgItem(IDC_EDIT22)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT20)->GetWindowTextW(exCS);
	exCSA = exCS;
	if (exCS.GetLength() != 0) {
		string exS((CT2A)exCS);
		long double size = stold(exS);
		if (size < 0 || size > 2) {
			MessageBox(CA2W("Expected value can be in interval of [0,2]"), NULL, MB_ICONERROR | MB_OK);
			GetDlgItem(IDC_EDIT20)->SetWindowTextW(CA2W(""));
		}
	}
	else if (exCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnTimeOutChange()
{
	CString toCS;
	CStringA toCSA;
	GetDlgItem(IDC_EDIT25)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT24)->GetWindowTextW(toCS);
	toCSA = toCS;
	if (toCS.GetLength() != 0) {
		int size = atoi(toCSA);
		if (size < 0 || size > 60) {
			MessageBox(CA2W("Timeout value can be in interval of [0,60]"), NULL, MB_ICONERROR | MB_OK);
			GetDlgItem(IDC_EDIT20)->SetWindowTextW(CA2W(""));
		}
	}
	else if (toCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnRatePercentChange()
{
	UpdateData(TRUE);
	CString perCS;
	CStringA perCSA;
	m_RateError.SetWindowTextW(CA2W(""));
	m_RatePercent.GetWindowTextW(perCS);
	perCSA = perCS;
	if (perCS.GetLength() != 0) {
		string perS((CT2A)perCS);
		long double percent = stold(perS);
		if (percent > 100 || percent < 0) {
			MessageBox(CA2W("% is 0~100\n Please insert valid value..."), CA2W("Percentage Correctness"), MB_ICONERROR | MB_OK);
			m_RatePercent.SetWindowTextW(CA2W(""));	// Deletes the invalid input
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
	m_SizeError.SetWindowTextW(CA2W(""));
	perCSA = perCS;
	if (perCS.GetLength() != 0) {

		int percent = atoi(perCSA);
		if (percent > 100 || percent < 1) {
			MessageBox(CA2W("% is 1~100\n Please insert valid value..."), CA2W("Percentage Correctness"), MB_ICONERROR | MB_OK);
			m_MigrationInPercent.SetWindowTextW(CA2W(""));	// Deletes the invalid input
		}
	}
	else if (perCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnPopulationSizeChange()
{
	UpdateData(TRUE);
	CString popCS;
	CStringA popCSA;
	m_PopulationSize.GetWindowTextW(popCS);
	m_PopError.SetWindowTextW(CA2W(""));
	popCSA = popCS;
	if (popCS.GetLength() != 0) {
		unsigned int size = atoi(popCSA);
		if (size < 1 || size > 20) {
			MessageBox(CA2W("Population size number can be in interval of [1,20]"), NULL, MB_ICONERROR | MB_OK);
			m_PopulationSize.SetWindowTextW(CA2W(""));
		}
	}
	else if (popCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnGenChange()
{
	UpdateData(TRUE);
	CString genCS;
	CStringA genCSA;
	m_GenerationsNum.GetWindowTextW(genCS);
	m_GenError.SetWindowTextW(CA2W(""));
	genCSA = genCS;
	if (genCS.GetLength() != 0) {
		unsigned int size = atoi(genCSA);
		if (size < 1 || size > 100) {
			MessageBox(CA2W("Generation number can be in interval of [1,100]"), NULL, MB_ICONERROR | MB_OK);
			m_GenerationsNum.SetWindowTextW(CA2W(""));
		}
	}
	else if (genCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnElitChange()
{
	UpdateData(TRUE);
	CString elitCS;
	CStringA elitCSA;
	m_ElitismNum.GetWindowTextW(elitCS);
	m_ElitError.SetWindowTextW(CA2W(""));
	elitCSA = elitCS;
	if (elitCS.GetLength() != 0) {
		unsigned int size = atoi(elitCSA);
		
		if ((size < 0 || size > 99 )){
			MessageBox(CA2W("Elitism number can be only EVEN number in interval of [0,99]"), NULL, MB_ICONERROR | MB_OK);
			m_ElitismNum.SetWindowTextW(CA2W(""));
		}
	}
	else if (elitCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnIterFixChange()
{
	UpdateData(TRUE);
	CString fixCS;
	CStringA fixCSA;
	m_IterationFix.GetWindowTextW(fixCS);
	m_FixError.SetWindowTextW(CA2W(""));
	fixCSA = fixCS;
	if (fixCS.GetLength() != 0) {
		unsigned int size = atoi(fixCSA);
		if (size < 1 || size > 100) {
			MessageBox(CA2W("Iteration fix number can be in interval of [1,99]"), NULL, MB_ICONERROR | MB_OK);
			m_IterationFix.SetWindowTextW(CA2W(""));
		}
	}
	else if (fixCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnEpsilonChange()
{
	UpdateData(TRUE);
	CString epsCS;
	CStringA epsCSA;
	m_Epsilon.GetWindowTextW(epsCS);
	m_EpsError.SetWindowTextW(CA2W(""));
	epsCSA = epsCS;
	if (epsCS.GetLength() != 0) {
		unsigned long size = atoi(epsCSA);
		if (size < 0 || size > 20000) {
			MessageBox(CA2W("Iteration fix number can be in interval of [(0),(20,000)]"), NULL, MB_ICONERROR | MB_OK);
			m_Epsilon.SetWindowTextW(CA2W(""));
		}
	}
	else if (epsCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnSizeKBChange()
{
	UpdateData(TRUE);
	CString sizeCS;
	CStringA sizeCSA;
	m_MigrationInKB.GetWindowTextW(sizeCS);
	m_SizeError.SetWindowTextW(CA2W(""));
	sizeCSA = sizeCS;
	if (sizeCS.GetLength() != 0) {
		unsigned long size = atoi(sizeCSA);
		if (size < 0 || size > 4294967295) {
			MessageBox(CA2W("Size for migration number can be in interval of [(0),(4,294,967,295)]"), NULL, MB_ICONERROR | MB_OK);
			m_MigrationInKB.SetWindowTextW(CA2W(""));
		}
	}
	else if (sizeCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnReset()
{
	// If the reset is performed after "Ok" button was pressed
	if (!read_input) {
		shared_ptr<GA_Migration> migControl(GA_Migration::GetCurInstance());
		migControl->SafeExit();
		delete m_resultDlg;
	}
	
	// Init error editors
	m_SelError.SetWindowTextW(CA2W(""));
	m_CrosError.SetWindowTextW(CA2W(""));
	m_MutError.SetWindowTextW(CA2W(""));
	m_PopError.SetWindowTextW(CA2W(""));
	m_RateError.SetWindowTextW(CA2W(""));
	m_GenError.SetWindowTextW(CA2W(""));
	m_ElitError.SetWindowTextW(CA2W(""));
	m_FixError.SetWindowTextW(CA2W(""));
	m_EpsError.SetWindowTextW(CA2W(""));
	m_SizeError.SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT25)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT23)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT22)->SetWindowTextW(CA2W(""));

	// Remain texts to clear
	m_SelectionCombo.SetCurSel(0);
	m_CrossComboBox.SetCurSel(0);
	m_MutationComboBox.SetCurSel(0);
	m_DiffrentMeasure.SetCurSel(0);
	m_EpsilonMeasure.SetCurSel(0);
	m_FilePath.SetWindowTextW(CA2W(""));
	m_PopulationSize.SetWindowTextW(CA2W(""));
	m_GenerationsNum.SetWindowTextW(CA2W(""));
	m_ElitismNum.SetWindowTextW(CA2W(""));
	m_IterationFix.SetWindowTextW(CA2W(""));
	m_Epsilon.SetWindowTextW(CA2W(""));
	m_MigrationInKB.SetWindowTextW(CA2W(""));
	m_MigrationInPercent.SetWindowTextW(CA2W(""));
	m_RatePercent.SetWindowTextW(CA2W(""));


	
	//	Reseting the enabled\disabled fields in the GUI
	EnableFields(false);
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT20)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT20)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT21)->SetWindowTextW(CA2W(""));
	GetDlgItem(IDC_EDIT24)->SetWindowTextW(CA2W(""));

	//	Other default values 
	true_KB = true;
	read_input = true;

	//	Example of input parameters
	m_PopulationSize.SetWindowTextW(CA2W("10"));
	m_RatePercent.SetWindowTextW(CA2W("15"));
	m_GenerationsNum.SetWindowTextW(CA2W("10"));
	m_ElitismNum.SetWindowTextW(CA2W("2"));
	m_IterationFix.SetWindowTextW(CA2W("3"));
	m_Epsilon.SetWindowTextW(CA2W("1"));
	m_MigrationInKB.SetWindowTextW(CA2W("500"));
	GetDlgItem(IDC_EDIT24)->SetWindowTextW(CA2W("5"));
	GetDlgItem(IDC_EDIT21)->SetWindowTextW(CA2W("15"));
	//	End Example of input parameters
}

/*
	Initialize general_prop's fields of GA_Migration instance
*/
void CFinalProjectDlg::InitVariables(shared_ptr<general_prop> properties)
{
	CString sel, cros, mut, rb_ExpVal, mutRate, timeOut, popSize, ratePer, genNum, eliNum, iterNumFix, epsilon, kb, perOfFile;
	CString byt_mea_size, eps_mea_size;

	// Convert to CString the text of the GUI components
	m_SelectionCombo.GetWindowTextW(sel);
	m_CrossComboBox.GetWindowTextW(cros);
	m_MutationComboBox.GetWindowTextW(mut);
	m_PopulationSize.GetWindowTextW(popSize);
	m_RatePercent.GetWindowTextW(ratePer);
	m_GenerationsNum.GetWindowTextW(genNum);
	m_ElitismNum.GetWindowTextW(eliNum);
	m_IterationFix.GetWindowTextW(iterNumFix);
	m_Epsilon.GetWindowTextW(epsilon);
	m_EpsilonMeasure.GetWindowTextW(eps_mea_size);
	GetDlgItem(IDC_EDIT20)->GetWindowTextW(rb_ExpVal);
	GetDlgItem(IDC_EDIT21)->GetWindowTextW(mutRate);
	GetDlgItem(IDC_EDIT24)->GetWindowTextW(timeOut);
	properties->trueFor_KB = true_KB;	//	Determined by handlers of radio buttons
	if (true_KB) {						//	Get appropriate information from GUI
		m_MigrationInKB.GetWindowTextW(kb);
		m_DiffrentMeasure.GetWindowTextW(byt_mea_size);
		if (byt_mea_size.Find(CString("K")) != -1)
			properties->g_kb_size = BytesMeasure::kilo;
		else if (byt_mea_size.Find(CString("M")) != -1)
			properties->g_kb_size = BytesMeasure::mega;
		else properties->g_kb_size = BytesMeasure::giga;
		string kbS((CT2A)kb);
		properties->g_kb = (stold(kbS));
	}
	else {								//	Get appropriate information from GUI
		m_MigrationInPercent.GetWindowTextW(perOfFile);
		string percS((CT2A)perOfFile);
		properties->g_percent = stold(percS);
	}

	// Update epsilon properties
	m_EpsilonMeasure.GetWindowTextW(eps_mea_size);
	if (eps_mea_size.Find(CA2W("K")) != -1)
		properties->g_eps_size = BytesMeasure::kilo;
	else if (eps_mea_size.Find(CA2W("M")) != -1)
		properties->g_eps_size = BytesMeasure::mega;
	else properties->g_eps_size = BytesMeasure::giga;
	string epsilonS((CT2A)epsilon);
	properties->g_epsilon = stold(epsilonS);

	// Update selection method
	if (sel.Find(CA2W("Roulette")) != -1)
		properties->g_sel_mode = Selection::rou_whe_sel;
	else if (sel.Find(CA2W("Linear")) != -1){
		properties->g_sel_mode = Selection::lin_rank_sel;
		string expS((CT2A)rb_ExpVal);
		properties->g_exp_val = stold(expS);
	}
	else properties->g_sel_mode = Selection::tour_sel;


	// Update crossover method
	if (cros.Find(CA2W("One")) != -1)
		properties->g_cros_mode = Crossover::one_point_cro;
	else if (cros.Find(CA2W("Two")) != -1)
		properties->g_cros_mode = Crossover::two_point_cro;
	else properties->g_cros_mode = Crossover::uni_cro;

	// Update mutation method
	if (mut.Find(CA2W("Single")) != -1)
		properties->g_mut_mode = Mutation::sin_point_mut;
	else properties->g_mut_mode = Mutation::uni_point_mut;

	string mutS((CT2A)mutRate);
	properties->g_mut_rate = stold(mutS);

	// Update the remain properties for the algorithm run
	properties->g_population_size = _ttoi(popSize);
	//std::string (ratePer, ratePer.GetLength());
	string rateS((CT2A)ratePer);
	properties->g_over_percent = stold(rateS);
	properties->g_generations = _ttoi(genNum);
	properties->g_start_fix = _ttoi(iterNumFix);
	properties->g_elit_best = _ttoi(eliNum);
	properties->g_timeOut = _ttoi(timeOut);
	properties->g_execTime = 0;
	properties->g_initTime = 0;
}

void CFinalProjectDlg::EnableFields(bool t)
{
	m_SelectionCombo.EnableWindow(t);
	m_CrossComboBox.EnableWindow(t);
	m_MutationComboBox.EnableWindow(t);
	m_PopulationSize.EnableWindow(t);
	m_RatePercent.EnableWindow(t);
	m_GenerationsNum.EnableWindow(t);
	m_ElitismNum.EnableWindow(t);
	m_IterationFix.EnableWindow(t);
	m_Epsilon.EnableWindow(t);
	m_EpsilonMeasure.EnableWindow(t);
	m_MigrationInKB.EnableWindow(t);
	m_MigrationInPercent.EnableWindow(t);
	m_DiffrentMeasure.EnableWindow(t);
	GetDlgItem(IDC_RADIO1)->EnableWindow(t);
	GetDlgItem(IDC_RADIO2)->EnableWindow(t);
	GetDlgItem(IDC_BUTTON2)->EnableWindow(t);
	GetDlgItem(IDOK)->EnableWindow(t);
	GetDlgItem(IDC_EDIT21)->EnableWindow(t);
	GetDlgItem(IDC_EDIT24)->EnableWindow(t);
}

/*
	OnBnClickedOk() taking care about the validation of the input
	-	Processing the string fro the user input
	-	Initialize bipratite-graph of blocks and files in such way that each file points to his associated blocks,
		and each block points to his associated files.
	-	Initialize general_properties struct which handles the technical information for GA run
*/
void CFinalProjectDlg::OnBnClickedOk()	
{
	chrono::duration<long double> initTime;
	chrono::duration<long double> execTime;
	ifstream input;
	CString s;
	CString sel, cros, mut, rb_ExpVal, mutRate, timeOut, popSize, ratePer, genNum, eliNum, iterNumFix, epsilon, kb, perOfFile;
	bool missed_field = false;
	//shared_ptr<GA_Migration> migControl(GA_Migration::GetCurInstance());
	GetDlgItem(IDOK)->EnableWindow(FALSE);
	// Initialize string - Original
	m_SelectionCombo.GetWindowTextW(sel);
	m_CrossComboBox.GetWindowTextW(cros);
	m_MutationComboBox.GetWindowTextW(mut);
	m_PopulationSize.GetWindowTextW(popSize);
	m_RatePercent.GetWindowTextW(ratePer);
	m_GenerationsNum.GetWindowTextW(genNum);
	m_ElitismNum.GetWindowTextW(eliNum);
	m_IterationFix.GetWindowTextW(iterNumFix);
	m_Epsilon.GetWindowTextW(epsilon);
	GetDlgItem(IDC_EDIT20)->GetWindowTextW(rb_ExpVal);
	GetDlgItem(IDC_EDIT21)->GetWindowTextW(mutRate);
	GetDlgItem(IDC_EDIT24)->GetWindowTextW(timeOut);
	if (true_KB) 
		m_MigrationInKB.GetWindowTextW(kb);
	else 
		m_MigrationInPercent.GetWindowTextW(perOfFile);

	// Check non-emptiness of every field - Remove caption for processing this code...
	if(sel.IsEmpty()) {
		m_SelError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(cros.IsEmpty()) {
		m_CrosError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(mut.IsEmpty()){
		m_MutError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if (m_SelectionCombo.GetCurSel() == 1) {
		if (rb_ExpVal.IsEmpty()) {
			GetDlgItem(IDC_EDIT22)->SetWindowTextW(CA2W("*"));
			missed_field = true;
		}
	}
	if (timeOut.IsEmpty()) {
		GetDlgItem(IDC_EDIT25)->SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if (mutRate.IsEmpty()) {
		GetDlgItem(IDC_EDIT23)->SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(popSize.IsEmpty()) {
		m_PopError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(ratePer.IsEmpty()){
		m_RateError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(genNum.IsEmpty()){
		m_GenError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(eliNum.IsEmpty()){
		m_ElitError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(iterNumFix.IsEmpty()){
		m_FixError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(epsilon.IsEmpty()){
		m_EpsError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if (true_KB) {
		if (kb.IsEmpty()){
			m_SizeError.SetWindowTextW(CA2W("*"));
			missed_field = true;
		}
	}
	else if(perOfFile.IsEmpty()){
		m_SizeError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}

	// Validation for missing fields - Remove caption for processing this code...
	if (missed_field) {
		MessageBox(CA2W("Please check the missing fields.\n Marked with '*'"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	
	// Check for logic between fields 
	CStringA genCSA, elitCSA, fixCSA, toCSA, popCSA;
	genCSA = genNum;
	elitCSA = eliNum;
	fixCSA = iterNumFix;
	toCSA = timeOut;
	popCSA = popSize;
	if (atoi(fixCSA) > atoi(genCSA)) {
		MessageBox(CA2W("Please check logic between #generation to #iteration-fix"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	if (atoi(elitCSA) % 2) {
		MessageBox(CA2W("Please notice that elitism number needs to be EVEN number"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	if (atoi(popCSA) % 2) {
		MessageBox(CA2W("Please notice that population size needs to be EVEN number"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	if (atoi(elitCSA) > atoi(popCSA)) {
		MessageBox(CA2W("Please check logic between Population size to elitism"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}
	/*
	string to = toCSA;
	if (to.find(".") != string::npos) {
		MessageBox(CA2W("time out field can be integer number"), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}*/
	
	// Validation of path field
	shared_ptr<GA_Migration> migControl(GA_Migration::GetCurInstance());
	if (read_input) {
		// Check non-empitness of path field
		m_FilePath.GetWindowTextW(s);
		if (s.IsEmpty()) {
			MessageBox(CA2W("Please select file from the file explorer to procced..."), NULL, MB_ICONERROR | MB_OK);
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			return;
		}

		// Open input file
		input.open(s);
		if (!input) {
			MessageBox(CA2W("Error loading text file, try again..."), NULL, MB_ICONERROR | MB_OK);
			GetDlgItem(IDOK)->EnableWindow(TRUE);
			return;
		}
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE); // Disable the option to choose another file from the browser, untill RESET		

		auto start = chrono::high_resolution_clock::now();

		//	Init file name and path
		migControl->SetFileName(string(CT2A(s.GetString())));

		// Process the input file and generate the bipratite-graph
		migControl->InitBipartiteGraph(input);

		// Close input file
		input.clear();
		input.close();

		auto end = chrono::high_resolution_clock::now();
		initTime = end - start;
		migControl->GetProperties()->g_initTime = initTime.count();

		// Sign for that a read been performed (for reset option...)
		read_input = false;
	}

	// Process general information from GUI for GA run
	InitVariables(migControl->GetProperties());

	// Check logic between migration size and system size
	migControl->InitKBForMig();
	if (migControl->GetProperties()->g_KBforMig > migControl->GetSystemSize()) {
		MessageBox(CA2W("Error: size for migration is bigger than the system size.\n please correct the size in KB for migration..."), NULL, MB_ICONERROR | MB_OK);
		GetDlgItem(IDOK)->EnableWindow(TRUE);
		return;
	}

	MessageBox(CA2W("Done inputting the data.\n Please wait a while for next message..."), NULL, MB_ICONEXCLAMATION | MB_OK);
	auto start = chrono::high_resolution_clock::now();

	// Run Genetic Algorithm!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	migControl->RunGeneticAlgo();

	auto end = chrono::high_resolution_clock::now();
	execTime = end - start;
	migControl->GetProperties()->g_execTime = execTime.count();

	//	Shows Output proccessing window after pressing OK
	if (MessageBox(CA2W("Done running Genetic-Algo"), NULL, MB_ICONASTERISK | MB_OK) == IDOK) {
		this->ShowWindow(SW_HIDE);
		m_resultDlg = new CResultDlg(this);
		m_resultDlg->Create(IDD_SECOND, this);
		m_resultDlg->ShowWindow(SW_SHOW);
	}
}

/*
	OnExitClick() taking care of terminating the control class of the GA
*/
void CFinalProjectDlg::OnExitClick()
{
	if (!read_input) {			// If there is need to clear the GA_Migration instance
		shared_ptr<GA_Migration> migControl(GA_Migration::GetCurInstance());
		migControl->SafeExit();
	}
	delete m_resultDlg;
	CDialogEx::OnCancel();
}

void CFinalProjectDlg::OnBnClickedButton3()
{
	MessageBox(CA2W("In this window you can browse for csv files which are formatted according to the input of the algorithm.\n * You have to choose the calculation for migration size within the input file.\n * You can try diffrent combinations of genetic operations.\n * tournament selection perform tournament among 4 chromosomes.\n * The program will show 2 popups during it's execution - in order to inform the user about the progress.\n * The results will be able to download in the next dialog"), NULL, MB_ICONASTERISK | MB_OK);
}
