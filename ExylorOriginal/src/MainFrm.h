// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__17968261_43E8_43D7_BE5C_5E35B01009E1__INCLUDED_)
#define AFX_MAINFRM_H__17968261_43E8_43D7_BE5C_5E35B01009E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

  void ViewOut();
  void ViewMod();
  void ViewDB();
  void ViewDBEdit();
  void ViewKB();
  void ViewKBEdit();
  void ViewRec();
  void ViewBM();
  void ViewExplan();   

// Attributes
public:

  // for Dynamic Menu
  CMenu m_NewMenu;
  HMENU m_hMenuDefault;
// Operations
public:

//  int OnChangeBitmap(BOOL DocExist);
 void CreateOrActivateFrame(CDocTemplate* pTemplate,
                                       CRuntimeClass* pViewClass);
  void OnReplaceMenu(int MenuID);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnUpdateTask(CCmdUI* pCmdUI);
    afx_msg void OnClose();
    afx_msg void OnRecognition();
    afx_msg void OnUpdateRecognition(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__17968261_43E8_43D7_BE5C_5E35B01009E1__INCLUDED_)
