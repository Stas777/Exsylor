#if !defined(AFX_GENKNOW_H__E9770E53_DE62_43E7_AE2E_77C01924B5E2__INCLUDED_)
#define AFX_GENKNOW_H__E9770E53_DE62_43E7_AE2E_77C01924B5E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenKnow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenKnow dialog

class CGenKnow : public CDialog
{
// Construction
public:
	CGenKnow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenKnow)
	enum { IDD = IDD_GEN_KNOW };
	int		m_nRow;
	int		m_nStart;
	int		m_nRank;
	int		m_nDensityProc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenKnow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGenKnow)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENKNOW_H__E9770E53_DE62_43E7_AE2E_77C01924B5E2__INCLUDED_)
