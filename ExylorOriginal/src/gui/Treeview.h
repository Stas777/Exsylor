// treeview.h : interface of the CTreeView class
// 17.05.2007
/////////////////////////////////////////////////////////////////////////////

class CTreeView : public CTrBzView
{
protected: // create from serialization only
  CTreeView();
  DECLARE_DYNCREATE(CTreeView)

// Attributes
public:
inline CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Operations
    void NextView();
    void ChangeColorRow(int nRow);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Overridables
    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
    int  GetActiveRow();
    int  GetRowCount();
    void OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected);
    void ChangeSelectionNextRow(BOOL bNext);
    void ChangeSelectionToRow(int nRow);
// Implementation
protected:
    // standard overrides of MFC classes
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

public:
  virtual ~CTreeView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
  //{{AFX_MSG(CTreeView)
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// class CTrRegView
/////////////////////////////////////////////////////////////////////////////
class CTrRegView : public CTrBzView
{
protected: // create from serialization only
  CTrRegView();
  DECLARE_DYNCREATE(CTrRegView)

// Operations
    void NextView();
// Attributes
public:
  inline CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
    void ChangeColorRow(int nRow);
    void WriteReg();
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    int  GetActiveRow();
    int  GetRowCount();
// Overridables
protected:
    void OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected);
    void ChangeSelectionNextRow(BOOL bNext);
    void ChangeSelectionToRow(int nRow);
// Implementation

protected:
    // standard overrides of MFC classes
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

// Implementation
public:
  virtual ~CTrRegView();

// Generated message map functions
protected:
  //{{AFX_MSG(CTrRegView)
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////////
// class CTrObView 
/////////////////////////////////////////////////////////////////////////////
class CTrObView : public CTrBzView
{
protected: // create from serialization only
  CTrObView();
  DECLARE_DYNCREATE(CTrObView)

// Attributes
public:
  inline CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Operations
    void NextView();
    void ChangeColorRow(int nRow);
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
// Overridables
    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
    int  GetActiveRow();
    int  GetRowCount();
    void OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected);
    void ChangeSelectionNextRow(BOOL bNext);
    void ChangeSelectionToRow(int nRow);
// Implementation
protected:
    // standard overrides of MFC classes
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);

public:
  virtual ~CTrObView();

#ifdef _DEBUG
  virtual void AssertValid() const;
  virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
  //{{AFX_MSG(CTrObView)
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
