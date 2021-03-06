// CResultDlg.cpp : implementation file
//
#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "FinalProject.h"
#include "CResultDlg.h"
#include "afxdialogex.h"


// CResultDlg dialog

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SECOND, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CResultDlg::~CResultDlg()
{
	
}

void CResultDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BOOL CResultDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	return TRUE;
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CResultDlg::OnCancelClick)
	ON_BN_CLICKED(IDC_BUTTON2, &CResultDlg::OnSaveClick)
END_MESSAGE_MAP()


// CResultDlg message handlers


void CResultDlg::OnCancelClick()
{
	CWnd* pDlg = AfxGetApp()->GetMainWnd();
	pDlg->ShowWindow(SW_SHOW);
	EndDialog(IDOK);
	CDialogEx::OnCancel();
}


void CResultDlg::OnSaveClick()
{
	fstream outStream;
	int i;
	bool allTimedOut = true;
	CFileDialog fileDlg(FALSE, CA2W("csv"), NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, CA2W("CSV Files (*.csv)|*.csv|||"), this);
	while (fileDlg.DoModal() == IDOK)
	{
		CString PathName = fileDlg.GetPathName();
		if (PathName.IsEmpty()) {
			MessageBox(CA2W("Please select CSV file from the file explorer to procced..."), NULL, MB_ICONERROR | MB_OK);
			return;
		}
		string pathS(CT2A(PathName.GetString()));
		if (!fileExists(pathS)) {	// File doesn't exist - Create new one...
			outStream.open(PathName.GetString(), fstream::out);
			if(outStream.is_open()){
				shared_ptr<GA_Evolution> ga_evo(GA_Evolution::GetCurInstance());
				shared_ptr<GA_Migration> ga_mig(GA_Migration::GetCurInstance());
				//	Init header of output
				outStream << "General Information about Migration process:" << "\n\n";

				outStream << "Initialize time of blocks and files[Seconds]:" << "," << ga_mig->GetProperties()->g_initTime << "\n";
				outStream << "Execution time of Genetic-Algorithm[Seconds]:" << "," << ga_mig->GetProperties()->g_execTime << "\n";

				outStream << "Proccessed file is:" << "," << ga_mig->GetFileName() << "\n";
				outStream << "Bytes for migration:" << ","
					<< fixed << ga_mig->GetProperties()->g_KBforMig << "\n";
				outStream << "Epsilon[Bytes]:" << "," << fixed << ga_mig->GetProperties()->g_epsilon << "\n";
				outStream << "Error Rate:" << "," << ga_mig->GetProperties()->g_over_percent << "%" << "\n\n";

				outStream << "Sizes for migratino (with considiration of: Error rate, Epsilon):\n";
				outStream << "Maximal size:" << "," << ga_mig->GetProperties()->g_KBforMig << " ,";
				outStream << "Minimal size:" << "," << ga_mig->GetProperties()->g_KB_minimal << "\n";

				outStream << "# files processed:" << ","
					<< ga_mig->GetNumberOfFiles() << "\n";
				outStream << "# Blocks processed:" << ","
					<< ga_mig->GetNumberOfBlocks() << "\n";
				outStream << "Total size of system:" << "," << ga_mig->GetSystemSize() << "\n\n\n";


				outStream << "Genetic-Algorithm information:" << "\n\n";

				outStream << "Evolution operations:" << "\n";
				outStream << ga_mig->SelectionString();
				if (ga_mig->SelectionString().find("Linear") != string::npos) 
					outStream << "," << "Expected Value:" << "," << ga_mig->GetProperties()->g_exp_val;
				outStream << "\n";
				outStream << ga_mig->CrossoverString() << "\n";
				outStream << ga_mig->MutationString() << "," << "Mutation Rate:" << ga_mig->GetProperties()->g_mut_rate << "%" << "\n";

				outStream << "Execution information" << "\n";
				outStream << "# Generations:" << "," << ga_mig->GetProperties()->g_generations << "\n";
				outStream << "Size of population:" << "," << ga_mig->GetProperties()->g_population_size << "\n";
				outStream << "# Elit chromosomes:" << "," << ga_mig->GetProperties()->g_elit_best << "\n";
				outStream << "# Iteration for start fix:" << "," << ga_mig->GetProperties()->g_start_fix << "\n";
				outStream << "TimeOut:" << "," << fixed << ga_mig->GetProperties()->g_timeOut << "\n\n\n";

				//	Write the result
				outStream << "Results:" << "\n\n";
				outStream << "Initial Population:" << "\n";
				for (auto it_chr : *ga_evo->GetInitialPopulation()->GetChromosomes()) {
					if (!it_chr->GetTimedOut()) allTimedOut = false;
				}
				i = 0;

				if(allTimedOut){
					//outStream << "Best Solution size:" << 0 << "\n";
					//if (ga_evo->GetInitialPopulation()->GetChromosomes()->at(0)->GetTimedOut())
					outStream << "Timeout solution" << "\n";
				}
				else {
					/*for (auto it = ga_evo->GetInitialPopulation()->GetChromosomes()->begin();
						it < ga_evo->GetInitialPopulation()->GetChromosomes()->end(); it++) {
						if ((*it)->GetTimedOut() == true)
							i++;
					}*/
					for (auto it_chr : *(ga_evo->GetInitialPopulation()->GetChromosomes())) {
						if(!it_chr->GetTimedOut()){
							outStream << "Chromosome #" << i << ",";
							outStream << "Best Solution size:" << fixed << ga_evo->GetInitialPopulation()->GetChromosomes()->at(i)->GetSolSize() << ",";
							outStream << "Migration size (Without neighboors of blocks):" << ga_evo->GetInitialPopulation()->GetChromosomes()->at(i)->GetMigSize() << "\n";
						}
						i++;
					}
					
				}

				outStream << "Final Population:" << "\n";

				//lastChrom = ga_evo->GetCurPopulation()->GetChromosomes()->back();
				i = 0;
				allTimedOut = true;
				for (auto it_chr : *ga_evo->GetInitialPopulation()->GetChromosomes()) {
					if (!it_chr->GetTimedOut()) allTimedOut = false;
				}

				if (allTimedOut) {
					//outStream << "Best Solution size:" << 0 << "\n";
					//if (ga_evo->GetCurPopulation()->GetChromosomes()->at(0)->GetTimedOut())
						outStream << "Timeout solution" << "\n";
				}
				else {
					/*for (auto it = ga_evo->GetCurPopulation()->GetChromosomes()->begin();
						it < ga_evo->GetCurPopulation()->GetChromosomes()->end(); it++) {
						if ((*it)->GetTimedOut() == true)
							i++;
					}*/
					for (auto it_chr : *(ga_evo->GetCurPopulation()->GetChromosomes())) {
						if (!it_chr->GetTimedOut()) {
							outStream << "Chromosome #" <<  i << ",";
							outStream << "Best Solution size: " << fixed << ga_evo->GetCurPopulation()->GetChromosomes()->at(i)->GetSolSize() << ",";;
							outStream << "Migration size (Without neighboors of blocks): " << ga_evo->GetCurPopulation()->GetChromosomes()->at(i)->GetMigSize() << "\n";
						}
						i++;
					}
					outStream << "The best set of block_sn which were found for migration:" << "\n";
					map<unsigned long, string> t_sns = ga_evo->GetInToKe();
					vector<unsigned long> t_migIndexes = ga_evo->GetCurPopulation()->GetChromosomes()->at(0)->GetMigratedIndexes();
					for (auto it_ind : t_migIndexes) {	// Output blocks which are going to migrate
						string b_sn = t_sns[it_ind];
						//if(ga_evo->GetCurPopulation()->GetChromosomes()->at(0)->GetMyBlocks()->find(b_sn))
						outStream << b_sn << ",";
					}
				}
				
				outStream.close();
				CWnd* pDlg = AfxGetApp()->GetMainWnd();
				pDlg->ShowWindow(SW_SHOW);
				CDialogEx::OnOK();
				return;
			}
			else {
				MessageBox(CA2W("File is probably already in use. Please try again later..."), NULL, MB_ICONERROR | MB_OK);
			}
		}
		else {	// Else...
			MessageBox(CA2W("File already exists in the specified directory. Please change name..."), NULL, MB_ICONERROR | MB_OK);
		}
	}
}


bool CResultDlg::fileExists(string fileName)
{
	ifstream infile(fileName);
	return infile.good();
}
