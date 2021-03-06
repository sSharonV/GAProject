
// FinalProjectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <atlimage.h>
#include <time.h>
#include "GA_Migration.h"
#include "CResultDlg.h"

class CResultDlg;

// CFinalProjectDlg dialog
class CFinalProjectDlg : public CDialogEx
{
// Construction
public:
	CFinalProjectDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINALPROJECT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBrowseClick();
	afx_msg void OnMigrationInKB();
	afx_msg void OnMigrationInPercent();
	afx_msg void OnCbSelection();
	afx_msg void OnRatePercentChange();
	afx_msg void OnCbnCrossover();
	afx_msg void OnCbnMutation();
	afx_msg void OnBnClickedOk();
	afx_msg void OnFilePercentChange();
	afx_msg void OnGenChange();
	afx_msg void OnElitChange();
	afx_msg void OnIterFixChange();
	afx_msg void OnEpsilonChange();
	afx_msg void OnSizeKBChange();
	afx_msg void OnReset();
	afx_msg void OnExitClick();
	afx_msg void OnPopulationSizeChange();
	afx_msg void OnExpectedValChange();
	afx_msg void OnMutationRateChange();
	afx_msg void OnTimeOutChange();

	bool true_KB;
	CStatic *braudeLogo;
	CImage viewImage;
	CBitmap viewBitmap;

	// Desribes the chosen file location
	CEdit m_FilePath;
	// ComboBox with the selection models we implemented
	CComboBox m_SelectionCombo;
	// ComboBox for the crossover models we implemented
	CComboBox m_CrossComboBox;
	// ComboBox for mutation models which were implemented
	CComboBox m_MutationComboBox;
	// Describes the number of iteration which the GA will perform 
	CEdit m_GenerationsNum;
	// Desribes the number of chromosomes to be stored as part of 'Elitism' principle
	CEdit m_ElitismNum;
	//  Desribes the iteration number in which a fix to the chromosomes will be performed after each iteration
	CEdit m_IterationFix;
	// Desribes the epislon which is allowed by the user for deviation of a solution 
	CEdit m_Epsilon;
	// Describes the KiloBytes for migration
	CEdit m_MigrationInKB;
	// Describes the percentage of the size for migration
	CEdit m_MigrationInPercent;
	// Describes the percentage of deviation within suggested solution
	CEdit m_RatePercent;
	// Defines if the given number is in Kilo\Mega\Giga bytes
	CComboBox m_DiffrentMeasure;
	// Defines measurement of bytes for epsilon field
	CComboBox m_EpsilonMeasure;
	// Handles the number of chromosomes for a given population
	CEdit m_PopulationSize;
	// Editors to display red '*' if any of the fields were missed
	CEdit m_SelError;
	CEdit m_CrosError;
	CEdit m_MutError;
	CEdit m_RateError;
	CEdit m_GenError;
	CEdit m_ElitError;
	CEdit m_FixError;
	CEdit m_EpsError;
	CEdit m_SizeError;
	CEdit m_PopError;

	
private:
	/*
		Initializing the properties of the GUI to intended structure
	*/
	void InitVariables(shared_ptr<general_prop> properties);

	/*
		Enables\Disables the fields of the GUI
	*/
	void EnableFields(bool t);

	/*
		Sign for that an input was performed
	*/
	bool read_input;

	/*
		Pointer to "Save" Dialog
	*/
	CResultDlg* m_resultDlg;
public:
	afx_msg void OnBnClickedButton3();
};
