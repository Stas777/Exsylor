// scriptvw.h : header file
// 17.05.2007

/////////////////////////////////////////////////////////////////////////////
// CScriptView form view

class CScriptView : public CFormView
{
    DECLARE_DYNCREATE(CScriptView)
protected:
    CScriptView();          // protected constructor used by dynamic creation

// Form Data
public:
    //{{AFX_DATA(CScriptView)
    enum { IDD = IDD_FORMA };
    int     m_nAttr;
    int     m_nDB;
    int     m_nKB;
    int     m_nModels;
    int     m_nVal;
    CString m_NameDB;
    CString m_NameKB;
    CString m_NameMod;
    int     m_nRegul;
    int     m_nSampl;
    //}}AFX_DATA

// Operations
   void OnUpdate(CView*, LPARAM lHint, CObject* pHint);
   void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Implementation
protected:
    virtual ~CScriptView();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    // Generated message map functions
    //{{AFX_MSG(CScriptView)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CRecogScriptView form view

class CRecogScriptView : public CFormView
{
    DECLARE_DYNCREATE(CRecogScriptView)
protected:
    CRecogScriptView();         // protected constructor used by dynamic creation

// Form Data
public:
    //{{AFX_DATA(CRecogScriptView)
    enum { IDD = IDD_RECOGNITION };
    CString m_NameKB;
    CString m_NameMod;
    int     m_nAttr;
    int     m_nVal;
    int     m_nRegul;
    //}}AFX_DATA

// Operations
   void OnUpdate(CView*, LPARAM lHint, CObject* pHint);
   void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

// Implementation
protected:
    virtual ~CRecogScriptView();
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    // Generated message map functions
    //{{AFX_MSG(CRecogScriptView)
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
