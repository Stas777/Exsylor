// 17.05.2007 -------------------------------------CBVView --  CBVRegView

/////////////////////////////////////////////////////////////////////////////
// CBVView
/////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
class CBVView : public CBrView
{
    DECLARE_DYNCREATE(CBVView)
public:
    CBVView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CBVView() {}
    // Generated message map functions
    //{{AFX_MSG(CBVView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBVRegView
/////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
class CBVRegView : public CBrView
{
    DECLARE_DYNCREATE(CBVRegView)
public:
    CBVRegView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CBVRegView() {}
    // Generated message map functions
    //{{AFX_MSG(CBVRegView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBVObView
/////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------
class CBVObView : public CBrView
{
    DECLARE_DYNCREATE(CBVObView)
public:
    CBVObView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CBVObView() {}
    // Generated message map functions
    //{{AFX_MSG(CBVObView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

