// brview.h : interface of the CBrView class
// 17.05.2007
//------------------------------------------

void PutNumber(CDC* pDC,int i,int y,CFont* FontOld,CFont* FontNew,LOGFONT* lf);

class CBrView : public CScrollView
{
    DECLARE_DYNAMIC(CBrView)
public:
    CBrView();

// Attributes

protected:
    int m_nRowWidth;            // width of row in current device units
    int m_nRowHeight;           // height of row in current device untis
    int m_nPrevRowCount;        // most recent row count, before update
    LOGFONT lf;

// Operations
// Overridables
public:
    virtual int GetRowCount() = 0;
    virtual void OnDrawRow(CDC* pDC, int nRowNo, int y) = 0;

protected:
    virtual void GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight);
    virtual void OnDraw(CDC* pDC);
// Implementation
    // standard overrides of MFC classes
    void OnInitialUpdate();
    virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
    virtual void CalculateRowMetrics(CDC* pDC)
                 { GetRowWidthHeight(pDC, m_nRowWidth, m_nRowHeight); }
    virtual void UpdateScrollSizes();
    virtual CRect RowToWndRect(CDC* pDC, int nRow);
    virtual int RowToYPos(int nRow);
    virtual void RectLPtoRowRange(const CRect& rLP,int& nFRow,int& nLRow, BOOL bPart);
    virtual int LastViewableRow();

    virtual ~CBrView();

// Generated message map functions
    //{{AFX_MSG(CBrView)
    afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
