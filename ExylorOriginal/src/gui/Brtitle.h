// 06.05.97 23:52 ------------------------------------
// brtitle.h : header file
//////////////////////////////////////////////////////
// CBrTitle view
class CBrTitle : public CScrollView
{ DECLARE_DYNCREATE(CBrTitle)
protected:
    CBrTitle();            // protected constructor used by dynamic creation

    int m_nRowWidth;            // width of row in current device units
    int m_nRowHeight;           // height of row in current device untis
    LOGFONT lf;

// Attributes
public:
    CScriptDoc* GetDocument()
        { ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CScriptDoc)));
          return (CScriptDoc*) m_pDocument; }

    virtual ~CBrTitle();
    virtual void OnDraw(CDC* pDC);      // overridden to draw this view
    virtual void OnUpdate(CView*, LPARAM lHint, CObject* pHint);
    void OnInitialUpdate();
    void CalculateRowMetrics(CDC* pDC);
    void UpdateScrollSizes();

    // Generated message map functions
    //{{AFX_MSG(CBrTitle)
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
