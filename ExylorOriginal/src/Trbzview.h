// trbzview.h : interface of the CTrBzView class
// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
void Draw(CDC* pDC,int j0,int x, int y);

class CTrBzView : public CBrView
{
protected: // create from serialization only
  CTrBzView();
  DECLARE_DYNAMIC(CTrBzView)

// Attributes
    int m_nPrevSelectedRow;     // index of the most recently selected row
public:
// Operations
    void UpdateRow(int nInvalidRow);    // called by derived class's
    virtual int GetActiveRow() = 0;
    int GetRowCount();
// standard overrides of MFC classes
    void OnInitialUpdate();
    void UpdateScrollSizes();
    void OnDraw(CDC* pDC);
    void OnDrawRow(CDC* pDC, int nRowNo, int y);
    virtual void OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected) = 0;
// Implementation

  virtual ~CTrBzView();

// Generated message map functions
protected:
  //{{AFX_MSG(CTrBzView)
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    //}}AFX_MSG
  DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
