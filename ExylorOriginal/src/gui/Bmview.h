// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
// CBMView

//------------------------------------------------------------------
class CBMView : public CBrView
{
    DECLARE_DYNCREATE(CBMView)
public:
    CBMView();

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
    virtual ~CBMView() {}
    // Generated message map functions
    //{{AFX_MSG(CBMView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CBMEditView

//------------------------------------------------------------------
class CBMEditView : public CBrView
{
    DECLARE_DYNCREATE(CBMEditView)
public:
    CBMEditView();

// Attributes
    int m_nPrevSelectedRow;

    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnInitialUpdate();
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);    
    void UpdateRow(int nInvalidRow);
    void ChangeSelectionNextRow(BOOL bNext);
    void ChangeSelectionToRow(int nRow);
    void NextView();
// Overrides of CBrView
    int  GetActSmp();
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CBMEditView() {}
    // Generated message map functions
    //{{AFX_MSG(CBMEditView)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CBMRegView

//------------------------------------------------------------------
class CBMRegView : public CBrView
{
    DECLARE_DYNCREATE(CBMRegView)
public:
    CBMRegView();

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
    virtual ~CBMRegView() {}
    // Generated message map functions
    //{{AFX_MSG(CBMRegView)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CBMEditView

//------------------------------------------------------------------
class CBMRegEditView : public CBrView
{
    DECLARE_DYNCREATE(CBMRegEditView)
public:
    CBMRegEditView();

// Attributes
    int m_nPrevSelectedRow;

    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Activation
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void OnInitialUpdate();
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    void UpdateRow(int nInvalidRow);
    void ChangeSelectionNextRow(BOOL bNext);
    void ChangeSelectionToRow(int nRow);
    void NextView();
// Overrides of CBrView
    int  GetActReg();
    int  GetRowCount();
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
// Implementation
protected:
    virtual ~CBMRegEditView() {}
    // Generated message map functions
    //{{AFX_MSG(CBMRegEditView)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CBMView

//------------------------------------------------------------------
class CBM_View : public CBrView
{
    DECLARE_DYNCREATE(CBM_View)
public:
    CBM_View();

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
    virtual ~CBM_View() {}
    // Generated message map functions
    //{{AFX_MSG(CBM_View)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

