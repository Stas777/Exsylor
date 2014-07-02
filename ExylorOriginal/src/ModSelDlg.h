#if !defined(AFX_MODELSELDLG)
#define AFX_MODELSELDLG

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModSelDlg.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CModSelDlg dialog
// 18.05.2007 ------------------------

class CModSelDlg : public CDialog
{
// Construction
public:
    CModSelDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
    //{{AFX_DATA(CModSelDlg)
    enum { IDD = IDD_BLOCK_SEL };
    CComboBox   m_cbModels;
    CString m_sName;
    CString m_Title;
    //}}AFX_DATA
// Implementation
protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Generated message map functions
    //{{AFX_MSG(CModSelDlg)
    virtual BOOL OnInitDialog();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODELSELDLG)
