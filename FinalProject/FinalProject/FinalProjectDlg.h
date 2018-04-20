
// FinalProjectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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

	

	
	
	
	
};
