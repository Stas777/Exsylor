#if !defined(AFX_MODDLG_H__2E9DB60E_3DB8_492F_8328_74A96AB7EED3__INCLUDED_)
#define AFX_MODDLG_H__2E9DB60E_3DB8_492F_8328_74A96AB7EED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModDlg dialog

class CModDlg : public CDialog
{
// Construction
public:
	CModDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModDlg)
	enum { IDD = IDD_MODELSCRIPT };
	CComboBox	m_cbVal;
	CComboBox	m_cbAttr;
	CString	m_ActAttr;
	CString	m_ActVal;
	int		m_nAttr;
	int		m_nVal;
	//}}AFX_DATA
  CkAttrArray* m_OpisAttr;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModDlg)
	afx_msg void OnSetfocusCombo1();
	afx_msg void OnSetfocusCombo2();
	afx_msg void OnSelendokCombo1();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnEditName();
	afx_msg void OnImport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODDLG_H__2E9DB60E_3DB8_492F_8328_74A96AB7EED3__INCLUDED_)
