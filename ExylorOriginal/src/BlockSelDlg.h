#if !defined(AFX_BLOCKSELDLG_H__37A19C34_2A99_4FDA_9A4F_8527B0A55443__INCLUDED_)
#define AFX_BLOCKSELDLG_H__37A19C34_2A99_4FDA_9A4F_8527B0A55443__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BlockSelDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BlockSelDlg dialog
// 18.05.2007 ------------------------

class BlockSelDlg : public CDialog
{
// Construction
public:
	BlockSelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(BlockSelDlg)
	enum { IDD = IDD_BLOCK_SEL };
	CComboBox	m_cbBlocks;
	CString	m_Title;
	CString m_sName;
	//}}AFX_DATA
  CBlockMap* m_pBMap;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BlockSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BlockSelDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BLOCKSELDLG_H__37A19C34_2A99_4FDA_9A4F_8527B0A55443__INCLUDED_)
