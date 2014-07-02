// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
// CWordView

//------------------------------------------------------------------
class CWordView : public CBrView
{
    DECLARE_DYNCREATE(CWordView)
public:
    CWordView();

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
    virtual ~CWordView() {}
    // Generated message map functions
    //{{AFX_MSG(CWordView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

//------------------------------------------------------------------
class CWordRegView : public CBrView
{
    DECLARE_DYNCREATE(CWordRegView)
public:
    CWordRegView();

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
    virtual ~CWordRegView() {}
    // Generated message map functions
    //{{AFX_MSG(CWordRegView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CStageView

//------------------------------------------------------------------
class CStageView : public CBrView
{
    DECLARE_DYNCREATE(CStageView)
public:
    CStageView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    void UpdateScrollSizes();
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CStageView() {}
    // Generated message map functions
    //{{AFX_MSG(CStageView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CExplanView

//------------------------------------------------------------------
class CExplanView : public CBrView
{
    DECLARE_DYNCREATE(CExplanView)
public:
    CExplanView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CExplanView() {}
    // Generated message map functions
    //{{AFX_MSG(CExplanView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CExplanStepView

//------------------------------------------------------------------
class CExplanStepView : public CBrView
{
    DECLARE_DYNCREATE(CExplanStepView)
public:
    CExplanStepView();

// Attributes
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
// Overrides of CBrView
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CExplanStepView() {}
    // Generated message map functions
    //{{AFX_MSG(CExplanStepView)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

