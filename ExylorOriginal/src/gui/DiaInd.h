#if !defined(AFX_DIAIND_H__947C16AE_35B3_42DA_A2A9_25D23F0551FA__INCLUDED_)
#define AFX_DIAIND_H__947C16AE_35B3_42DA_A2A9_25D23F0551FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DiaInd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDiaInd dialog

class CDiaInd : public CDialog
{
// Construction
public:
	CDiaInd(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDiaInd)
	enum { IDD = IDD_IND };
	BOOL	m_chRank;
	BOOL	m_chNumber;
	BOOL	m_chProb;
	int		m_Rank;
	int		m_Number;
	int		m_Power;
	CString	m_1;
	CString	m_2;
	CString	m_3;
	CString	m_4;
	CString	m_5;
	CString	m_6;
	CString	m_7;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDiaInd)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDiaInd)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIAIND_H__947C16AE_35B3_42DA_A2A9_25D23F0551FA__INCLUDED_)
