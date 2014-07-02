// modview.h : interface of the CModView class
// 17.05.2007 
/////////////////////////////////////////////////////////////////////////////

class CModView : public CBrView
{
protected: // create from serialization only
  CModView();
  DECLARE_DYNCREATE(CModView)

// Attributes
public:
inline CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

// Operations
    void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
    int GetRowCount();
    void OnDrawRow(CDC* pDC, int nRow, int y);

// Overridables
    // standard overrides of MFC classes
    void OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
    void OnUpdate(CView* pSender, LPARAM lHint = 0L, CObject* pHint = NULL);
    void UpdateScrollSizes();
    virtual ~CModView();

// Generated message map functions
protected:
  //{{AFX_MSG(CModView)
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
