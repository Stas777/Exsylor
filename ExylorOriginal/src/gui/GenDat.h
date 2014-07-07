#if !defined(AFX_GENDAT_H__EE35E347_9615_48A5_A52E_46D5C469E61C__INCLUDED_)
#define AFX_GENDAT_H__EE35E347_9615_48A5_A52E_46D5C469E61C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GenDat.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGenDat dialog

class CGenDat : public CDialog
{
// Construction
public:
	CGenDat(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGenDat)
	enum { IDD = IDD_GEN_DAT };
	int		m_nRow;
	int		m_nStart;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGenDat)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGenDat)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GENDAT_H__EE35E347_9615_48A5_A52E_46D5C469E61C__INCLUDED_)
