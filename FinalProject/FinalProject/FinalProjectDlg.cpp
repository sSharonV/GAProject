
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
	DDX_Control(pDX, IDC_EDIT10, m_SelError);
	DDX_Control(pDX, IDC_EDIT11, m_CrosError);
	DDX_Control(pDX, IDC_EDIT12, m_MutError);
	DDX_Control(pDX, IDC_EDIT13, m_RateError);
	DDX_Control(pDX, IDC_EDIT14, m_GenError);
	DDX_Control(pDX, IDC_EDIT15, m_ElitError);
	DDX_Control(pDX, IDC_EDIT16, m_FixError);
	DDX_Control(pDX, IDC_EDIT17, m_EpsError);
	DDX_Control(pDX, IDC_EDIT18, m_SizeError);
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
	// Radio buttons
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(FALSE);
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
	true_KB = true;
}


void CFinalProjectDlg::OnMigrationInPercent()
{
	m_MigrationInPercent.EnableWindow(TRUE);
	m_MigrationInKB.EnableWindow(FALSE);
	true_KB = false;
}

void CFinalProjectDlg::OnCbSelection()
{
	m_SelError.SetWindowTextW(CA2W(""));
}

void CFinalProjectDlg::OnCbnCrossover()
{
	m_CrosError.SetWindowTextW(CA2W(""));
}

void CFinalProjectDlg::OnCbnMutation()
{
	m_MutError.SetWindowTextW(CA2W(""));
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

		int percent = atoi(perCSA);
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
		if (percent > 100 || percent < 0) {
			MessageBox(CA2W("% is 0~100\n Please insert valid value..."), CA2W("Percentage Correctness"), MB_ICONERROR | MB_OK);
			m_MigrationInPercent.SetWindowTextW(CA2W(""));	// Deletes the invalid input
		}
	}
	else if (perCS.GetLength() == 0) {}
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
		if (size < 0 || size > 99) {
			MessageBox(CA2W("Elitism number can be in interval of [0,99]"), NULL, MB_ICONERROR | MB_OK);
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
		if (size < 1 || size > 20000) {
			MessageBox(CA2W("Iteration fix number can be in interval of [(1),(20,000)]"), NULL, MB_ICONERROR | MB_OK);
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
		if (size < 1 || size > 4294967295) {
			MessageBox(CA2W("Iteration fix number can be in interval of [(1),(4,294,967,295)]"), NULL, MB_ICONERROR | MB_OK);
			m_MigrationInKB.SetWindowTextW(CA2W(""));
		}
	}
	else if (sizeCS.GetLength() == 0) {}
	else MessageBox(CA2W("Some ERROR"), NULL, MB_ICONERROR | MB_OK);
}

void CFinalProjectDlg::OnReset()
{
	GA_Migration *migControl = GA_Migration::GetCurInstance();	// delete all the information loaded by the previous instance of the main control class
	migControl->SafeExit();	
	delete migControl;
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
	// Remain texts to clear
	m_SelectionCombo.SetWindowTextW(CA2W(""));
	m_CrossComboBox.SetWindowTextW(CA2W(""));
	m_MutationComboBox.SetWindowTextW(CA2W(""));
	m_FilePath.SetWindowTextW(CA2W(""));
	m_GenerationsNum.SetWindowTextW(CA2W(""));
	m_ElitismNum.SetWindowTextW(CA2W(""));
	m_IterationFix.SetWindowTextW(CA2W(""));
	m_Epsilon.SetWindowTextW(CA2W(""));
	m_MigrationInKB.SetWindowTextW(CA2W(""));
	m_MigrationInPercent.SetWindowTextW(CA2W(""));
	m_RatePercent.SetWindowTextW(CA2W(""));
	//
	m_MigrationInPercent.EnableWindow(FALSE);
	m_MigrationInKB.EnableWindow(TRUE);
	true_KB = true;
	GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
}

general_prop CFinalProjectDlg::InitVariables()
{
	general_prop properties;
	CString sel, cros, mut, ratePer, genNum, eliNum, iterNumFix, epsilon, kb, perOfFile;

	// Convert to CString the text of the GUI components
	m_SelectionCombo.GetWindowTextW(sel);
	m_CrossComboBox.GetWindowTextW(cros);
	m_MutationComboBox.GetWindowTextW(mut);
	m_RatePercent.GetWindowTextW(ratePer);
	m_GenerationsNum.GetWindowTextW(genNum);
	m_ElitismNum.GetWindowTextW(eliNum);
	m_IterationFix.GetWindowTextW(iterNumFix);
	m_Epsilon.GetWindowTextW(epsilon);
	properties.trueFor_KB = true_KB;
	if (true_KB) {
		m_MigrationInKB.GetWindowTextW(kb);
		properties.g_kb = _ttoi(kb);
	}
	else {
		m_MigrationInPercent.GetWindowTextW(perOfFile);
		properties.g_percent = _ttoi(perOfFile);
	}

	// Update selection method
	if (sel.Find(CA2W("Roulette")))
		properties.g_sel_mode = Selection::rou_whe_sel;
	else if (sel.Find(CA2W("Linear")))
		properties.g_sel_mode = Selection::lin_rank_sel;
	else properties.g_sel_mode = Selection::tour_sel;

	// Update crossover method
	if (cros.Find(CA2W("One")))
		properties.g_cros_mode = Crossover::one_point_cro;
	else if (cros.Find(CA2W("Two")))
		properties.g_cros_mode = Crossover::two_point_cro;
	else properties.g_cros_mode = Crossover::uni_cro;

	// Update mutation method
	if (mut.Find(CA2W("Single")))
		properties.g_mut_mode = Mutation::sin_point_mut;
	else properties.g_mut_mode = Mutation::uni_point_mut;

	// Update the remain properties for the algorithm run
	properties.g_over_percent = _ttoi(ratePer);
	properties.g_generations = _ttoi(genNum);
	properties.g_elit_best = _ttoi(eliNum);
	properties.g_start_fix = _ttoi(iterNumFix);
	properties.g_epsilon = _ttoi(epsilon);
	return properties;
}

void CFinalProjectDlg::OnBnClickedOk()
{
	ifstream input;
	CString s;
	CString sel, cros, mut, ratePer, genNum, eliNum, iterNumFix, epsilon, kb, perOfFile;
	bool missed_field = false;
	GA_Migration *migControl = GA_Migration::GetCurInstance();
	m_SelectionCombo.GetWindowTextW(sel);
	m_CrossComboBox.GetWindowTextW(cros);
	m_MutationComboBox.GetWindowTextW(mut);
	m_RatePercent.GetWindowTextW(ratePer);
	m_GenerationsNum.GetWindowTextW(genNum);
	m_ElitismNum.GetWindowTextW(eliNum);
	m_IterationFix.GetWindowTextW(iterNumFix);
	m_Epsilon.GetWindowTextW(epsilon);
	if (true_KB) 
		m_MigrationInKB.GetWindowTextW(kb);
	else 
		m_MigrationInPercent.GetWindowTextW(perOfFile);
	
	// Check non-emptiness of every field
	if (sel.IsEmpty()) {
		m_SelError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if (cros.IsEmpty()) {
		m_CrosError.SetWindowTextW(CA2W("*"));
		missed_field = true;
	}
	if(mut.IsEmpty()){
		m_MutError.SetWindowTextW(CA2W("*"));
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
	/*
	if (missed_field) {
		MessageBox(CA2W("Please check the missing fields.\n Marked with '*'"), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	
	// Check for logic between fields 
	CStringA genCSA, elitCSA, fixCSA;
	genCSA = genNum;
	elitCSA = eliNum;
	fixCSA = iterNumFix;
	if (atoi(genCSA) < atoi(elitCSA)) {
		MessageBox(CA2W("Please check logic between #generation to #elitism"), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	if (atoi(fixCSA) > atoi(genCSA)) {
		MessageBox(CA2W("Please check logic between #generation to #iteration-fix"), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	*/
	// Check validation of path fields
	m_FilePath.GetWindowTextW(s);
	if (s.IsEmpty()) {
		MessageBox(CA2W("Please select file from the file explorer to procced..."), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	
	input.open(s);
	if (!input) {
		MessageBox(CA2W("Error loading text file, try again..."), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	
	// Process the input file
	migControl->InitBipartiteGraph(input);
	input.close();
	CStringA kbCSA;
	kbCSA = kb;
	if (strtold((LPCSTR)kbCSA, NULL) > migControl->GetSolutionLimitSize()) {
		MessageBox(CA2W("Error: size for migration is bigger than the system size.\n please correct the size in KB for migration..."), NULL, MB_ICONERROR | MB_OK);
		return;
	}
	// Process general information for the GA run
	migControl->SetGeneralProperties(InitVariables());
	CDialogEx::OnOK();
}

void CFinalProjectDlg::OnExitClick()
{
	GA_Migration *migControl = GA_Migration::GetCurInstance();
	migControl->SafeExit();
	delete migControl;
	CDialogEx::OnCancel();
}
