// splitter.h : custom splitter control and frame that contains it
// 17.05.2007
//-----------------------------------------------------------------
// CSplitterFrame frame with splitter/wiper

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitRecognFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitRecognFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitRecognFrame)
protected:
    CSplitRecognFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter; 
    CSplitterWnd m_wndSplitter1;
    CSplitterWnd m_wndSplitter2;
// Operations
public:
// Implementation
    virtual ~CSplitRecognFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitRecognFrame)
    afx_msg void OnClose();    
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitModFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitModFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitModFrame)
protected:
    CSplitModFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
// Operations
public:
// Implementation
    virtual ~CSplitModFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitModFrame)
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitDBFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitDBFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitDBFrame)
protected:
    CSplitDBFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
    CSplitterWnd m_wndSplitter1;
// Operations
public:
// Implementation
    virtual ~CSplitDBFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitDBFrame)
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitDBEditFrame
/////////////////////////////////////////////////////////////////////////
class CSplitDBEditFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitDBEditFrame)
protected:
    CSplitDBEditFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
    CSplitterWnd m_wndSplitter1;
// Operations
public:
// Implementation
    virtual ~CSplitDBEditFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitDBEditFrame)
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitKBFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitKBFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitKBFrame)
protected:
    CSplitKBFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
    CSplitterWnd m_wndSplitter1;
// Operations
public:
// Implementation
    virtual ~CSplitKBFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );

    // Generated message map functions
    //{{AFX_MSG(CSplitKBFrame)
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};



/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitKBEditFrame
/////////////////////////////////////////////////////////////////////////
class CSplitKBEditFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitKBEditFrame)
protected:
    CSplitKBEditFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
    CSplitterWnd m_wndSplitter1;
// Operations
public:
// Implementation
    virtual ~CSplitKBEditFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );

    // Generated message map functions
    //{{AFX_MSG(CSplitKBEditFrame)
    afx_msg void OnClose();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitViewBMFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitViewBMFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitViewBMFrame)
protected:
    CSplitViewBMFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter;
// Operations
public:
// Implementation
    virtual ~CSplitViewBMFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitViewBMFrame)
    afx_msg void OnClose();
    afx_msg void OnViewExit();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
//  CSplitExplanFrame
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
class CSplitExplanFrame : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CSplitExplanFrame)
protected:
    CSplitExplanFrame();   // protected constructor used by dynamic creation

// Attributes
protected:
    CSplitterWnd m_wndSplitter; 
// Operations
public:
// Implementation
    virtual ~CSplitExplanFrame();
    virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    // Generated message map functions
    //{{AFX_MSG(CSplitExplanFrame)
    afx_msg void OnClose();    
    afx_msg void OnViewExplanExit();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CIndWnd frame

class CIndWnd : public CMDIChildWnd
{
    DECLARE_DYNCREATE(CIndWnd)
protected:
    CIndWnd();          // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
    BOOL PreCreateWindow( CREATESTRUCT& cs );
    void OnClose();
// Implementation
protected:
    virtual ~CIndWnd();

    // Generated message map functions
    //{{AFX_MSG(CIndWnd)
        // NOTE - the ClassWizard will add and remove member functions here.
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
