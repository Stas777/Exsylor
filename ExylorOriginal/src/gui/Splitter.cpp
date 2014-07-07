// splitter.cpp : implementation file
// 17.05.2007
//---------------------------------------------------------------

#include "stdafx.h"
#include "exsylor.h"
#include "scrdoc.h"
#include "scriptvw.h"
#include "splitter.h"
#include "brview.h"
#include "trbzview.h"
#include "brtitle.h"
#include "bmview.h"
#include "modview.h"
#include "bvview.h"
#include "treeview.h"
#include "wordview.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int indW;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitRecognFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitRecognFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitRecognFrame

// Create a splitter window which splits an output text view and an input view
//               
//  CModelBaze (CFormView)
//---------------------------------------------------------------
//  CModView   (CScrollView)
//---------------------------------------------------------------


IMPLEMENT_DYNCREATE(CSplitRecognFrame, CMDIChildWnd)

CSplitRecognFrame::CSplitRecognFrame()   { }
CSplitRecognFrame::~CSplitRecognFrame()  { }  //WM_CANCELMODE

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitRecognFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{ 
  if (!m_wndSplitter.CreateStatic(this, 2, 1,WS_CHILD | WS_VISIBLE | WS_BORDER))  // create a splitter with 1 row, 2 columns
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetRowInfo(0,16,16);
  m_wndSplitter.SetRowInfo(1,252,180);

  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CStageView), CSize( 0,16), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
    
    
  if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 1, 2, 
      WS_CHILD | WS_VISIBLE | WS_BORDER,m_wndSplitter.IdFromRowCol(1, 0)))   // create a splitter with 1 row, 2 columns
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter1.SetColumnInfo(0,230,120);
  m_wndSplitter1.SetColumnInfo(1,300,120);

  if (!m_wndSplitter2.CreateStatic(&m_wndSplitter1, 4, 1,
       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL,  // style, WS_BORDER is needed
       m_wndSplitter1.IdFromRowCol(0, 1)))
   { TRACE("Failed to create nested splitter\n"); return FALSE; }
  m_wndSplitter2.SetRowInfo(0,28,16);
  m_wndSplitter2.SetRowInfo(1,17,12);
  m_wndSplitter2.SetRowInfo(2,118,60);
  m_wndSplitter2.SetRowInfo(3,80,60);

  if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CTrObView), CSize(230,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter2.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter2.CreateView(1, 0, RUNTIME_CLASS(CBVObView), CSize(0,17), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter2.CreateView(2, 0, RUNTIME_CLASS(CBMRegView), CSize(0,118), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter2.CreateView(3, 0, RUNTIME_CLASS(CWordView), CSize(0,80), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter1.GetPane(0,0)); // activate the input view
  return TRUE;
}

//--------------------------------------------------------------------PreCreateWindow
BOOL CSplitRecognFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE;  cs.cy=600;  cs.cx=630; cs.y=24;  cs.x=186;
  return CMDIChildWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------OnClose
void CSplitRecognFrame::OnClose()
{ theApp.CurrentTask&=~(AIM); CMDIChildWnd::OnClose(); }

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitModFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitModFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitModFrame

// Create a splitter window which splits an output text view and an input view
//               |
//  CScriptView  | CModView
//  (CFormView)  | (CScrollView)
//               |
//---------------------------------------------------------------


IMPLEMENT_DYNCREATE(CSplitModFrame, CMDIChildWnd)

CSplitModFrame::CSplitModFrame()   { }
CSplitModFrame::~CSplitModFrame()  { }  //WM_CANCELMODE

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitModFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
  if (!m_wndSplitter.CreateStatic(this, 1, 2))  // create a splitter with 1 row, 2 columns
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetColumnInfo(0,178,80);
  m_wndSplitter.SetColumnInfo(1,200,100);

  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CScriptView), CSize( 178,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CModView), CSize(200,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(0,1)); // activate the input view
  return TRUE;
}

//--------------------------------------------------------------------PreCreateWindow
BOOL CSplitModFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE;  cs.cy=640;  cs.cx=480; cs.y=0;  cs.x=0;
  return CMDIChildWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------OnClose
void CSplitModFrame::OnClose()
{ if (theApp.CurrentTask>0) AfxMessageBox(IDS_IMPOSSIBLE);
  else  CMDIChildWnd::OnClose();
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitDBFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitDBFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitDBFrame

// Create a splitter window which splits an output text view and an input view
//                |  CBrTitle  (CScrollView)
//  CTreeView     |------------------
//  (CScrollView) |  CBVView   (CBrView)
//                |------------------
//                |  CBMView   (CBrView)
//                |------------------
//                |  CWordView (CBrView)
//---------------------------------------------------------------

IMPLEMENT_DYNCREATE(CSplitDBFrame, CMDIChildWnd)

CSplitDBFrame::CSplitDBFrame()   { }
CSplitDBFrame::~CSplitDBFrame()  { }

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitDBFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
  if (!m_wndSplitter.CreateStatic(this, 1, 2))   // create a splitter with 1 row, 2 columns
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
   m_wndSplitter.SetColumnInfo(0,240,120);
   m_wndSplitter.SetColumnInfo(1,400,120);

  if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 4, 1,
       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL,  // style, WS_BORDER is needed
       m_wndSplitter.IdFromRowCol(0, 1)))
   { TRACE("Failed to create nested splitter\n"); return FALSE; }
  m_wndSplitter1.SetRowInfo(0,28,16);
  m_wndSplitter1.SetRowInfo(1,17,12);
  m_wndSplitter1.SetRowInfo(2,152,80);
  m_wndSplitter1.SetRowInfo(3,150,60);

  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTreeView), CSize(240,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CBVView), CSize(0,17), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(2, 0, RUNTIME_CLASS(CBMView), CSize(0,152), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(3, 0, RUNTIME_CLASS(CWordView), CSize(0,150), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(0,0)); // activate the input view
  return TRUE;
}

//----------------------------------------------------------------------PreCreateWindow
BOOL CSplitDBFrame::PreCreateWindow( CREATESTRUCT& cs )
{  cs.style &= ~(LONG)FWS_ADDTOTITLE; cs.cy=600; cs.cx=800; cs.x=188; cs.y=24;
   return CMDIChildWnd::PreCreateWindow(cs);
}

//----------------------------------------------------------------------OnClose
void CSplitDBFrame::OnClose()
{ CDocument* pDoc = GetActiveDocument();  ASSERT(pDoc != NULL);
 if (pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc)))
   if (theApp.CurrentTask&NEW_SAMPLE) {
     CScriptDoc* pScrD;  pScrD = (CScriptDoc*)pDoc;  pScrD ->DBClose(TRUE);
     CMDIChildWnd::OnClose();
   }
}



///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitDBEditFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitDBEditFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitDBEditFrame

// Create a splitter window which splits an output text view and an input view
//                |  CBrTitle  (CScrollView)
//  CTreeView     |------------------
//  (CScrollView) |  CBVView   (CBrView)
//                |------------------
//                |  CBMView   (CBrView)
//                |------------------
//                |  CWordView (CBrView)
//---------------------------------------------------------------

IMPLEMENT_DYNCREATE(CSplitDBEditFrame, CMDIChildWnd)

CSplitDBEditFrame::CSplitDBEditFrame()   { }
CSplitDBEditFrame::~CSplitDBEditFrame()  { }

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitDBEditFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
  if (!m_wndSplitter.CreateStatic(this, 1, 2))
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
   m_wndSplitter.SetColumnInfo(0,240,120);
   m_wndSplitter.SetColumnInfo(1,400,120);

  if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 4, 1,
       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL,  // style, WS_BORDER is needed
       m_wndSplitter.IdFromRowCol(0, 1)))
   { TRACE("Failed to create nested splitter\n"); return FALSE; }
  m_wndSplitter1.SetRowInfo(0,28,16);
  m_wndSplitter1.SetRowInfo(1,17,12);
  m_wndSplitter1.SetRowInfo(2,152,80);
  m_wndSplitter1.SetRowInfo(3,150,60);

  if (!m_wndSplitter.CreateView(0, 0,  RUNTIME_CLASS(CTreeView), CSize(240,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CBVView), CSize(0,17), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(2, 0, RUNTIME_CLASS(CBMEditView), CSize(0,152), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(3, 0, RUNTIME_CLASS(CWordView), CSize(0,150), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(0,0));  // activate the input view
  return TRUE;
}

//--------------------------------------------------------------------PreCreateWindow
BOOL CSplitDBEditFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE;  cs.cy=600; cs.cx=800; cs.x=188; cs.y=24;
  return CMDIChildWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------OnClose
void CSplitDBEditFrame::OnClose()
{ CDocument* pDoc = GetActiveDocument(); ASSERT(pDoc != NULL);
 if (pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc))) 
   if (theApp.CurrentTask&EDIT_DB) {
     CScriptDoc* pScrD;  pScrD = (CScriptDoc*)pDoc; pScrD ->DBClose(TRUE);
     CMDIChildWnd::OnClose();
   }
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitKBFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitKBFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitKBFrame

// Create a splitter window which splits an output text view and an input view
//                |  CBrTitle  (CScrollView)
//  CTreeView     |------------------  
//  (CScrollView) |  CBVView   (CBrView)
//                |------------------  
//                |  CBMView   (CBrView)
//                |------------------
//                |  CWordView (CBrView)
//---------------------------------------------------------------

IMPLEMENT_DYNCREATE(CSplitKBFrame, CMDIChildWnd)

CSplitKBFrame::CSplitKBFrame()   { }
CSplitKBFrame::~CSplitKBFrame()  { }

//--------------------------------------------------------------------
BOOL CSplitKBFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
  if (!m_wndSplitter.CreateStatic(this, 1, 2))
    { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetColumnInfo(0,240,120);
  m_wndSplitter.SetColumnInfo(1,400,120);

  if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 4, 1,
       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL,  // style, WS_BORDER is needed
       m_wndSplitter.IdFromRowCol(0, 1)))  
   { TRACE("Failed to create nested splitter\n"); return FALSE; }
  m_wndSplitter1.SetRowInfo(0,28,16);
  m_wndSplitter1.SetRowInfo(1,17,12);
  m_wndSplitter1.SetRowInfo(2,152,80);
  m_wndSplitter1.SetRowInfo(3,150,60);

  if (!m_wndSplitter.CreateView(0, 0,  RUNTIME_CLASS(CTrRegView), CSize(240,0), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CBVRegView), CSize(0,17), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(2, 0, RUNTIME_CLASS(CBMRegView), CSize(0,152), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(3, 0, RUNTIME_CLASS(CWordRegView), CSize(0,150), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(0,0));  // activate the input view
  return TRUE;
}

//--------------------------------------------------------
BOOL CSplitKBFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE; cs.cy=600; cs.cx=800; cs.x=188; cs.y=24;
    return CMDIChildWnd::PreCreateWindow(cs);
}

//----------------------------------------------------------OnClose
void CSplitKBFrame::OnClose()
{ CDocument* pDoc = GetActiveDocument(); ASSERT(pDoc != NULL);
 if (pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc))) 
   if (theApp.CurrentTask&NEW_REGUL) {
     CScriptDoc* pScrD; pScrD = (CScriptDoc*)pDoc; pScrD ->KBClose(TRUE);
     CMDIChildWnd::OnClose();
   }
}


///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitKBEditFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitKBEditFrame)
    ON_WM_CLOSE()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitKBEditFrame

// Create a splitter window which splits an output text view and an input view
//                |  CBrTitle  (CScrollView)
//  CTreeView     |------------------  
//  (CScrollView) |  CBVView   (CBrView)
//                |------------------  
//                |  CBMView   (CBrView)
//                |------------------
//                |  CWordView (CBrView)
//---------------------------------------------------------------

IMPLEMENT_DYNCREATE(CSplitKBEditFrame, CMDIChildWnd)

CSplitKBEditFrame::CSplitKBEditFrame()   { }
CSplitKBEditFrame::~CSplitKBEditFrame()  { }

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitKBEditFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{
  if (!m_wndSplitter.CreateStatic(this, 1, 2))
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetColumnInfo(0,240,120);
  m_wndSplitter.SetColumnInfo(1,400,120);

  if (!m_wndSplitter1.CreateStatic(&m_wndSplitter, 4, 1,
       WS_CHILD | WS_VISIBLE | WS_BORDER | WS_HSCROLL,  // style, WS_BORDER is needed
       m_wndSplitter.IdFromRowCol(0, 1)))
   { TRACE("Failed to create nested splitter\n"); return FALSE; }
  m_wndSplitter1.SetRowInfo(0,28,16);
  m_wndSplitter1.SetRowInfo(1,17,12);
  m_wndSplitter1.SetRowInfo(2,152,80);
  m_wndSplitter1.SetRowInfo(3,150,60);

  if (!m_wndSplitter.CreateView(0, 0,  RUNTIME_CLASS(CTrRegView), CSize(240,0), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(1, 0, RUNTIME_CLASS(CBVRegView), CSize(0,17), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(2, 0, RUNTIME_CLASS(CBMRegEditView), CSize(0,152), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter1.CreateView(3, 0, RUNTIME_CLASS(CWordRegView), CSize(0,150), pContext))
     { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(0,0)); // activate the input view
  return TRUE;
}

//------------------------------------------------------------------------PreCreateWindow
BOOL CSplitKBEditFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE; cs.cy=600; cs.cx=800; cs.x=188; cs.y=24;
  return CMDIChildWnd::PreCreateWindow(cs);
}

//------------------------------------------------------------------------OnClose
void CSplitKBEditFrame::OnClose()
{ CDocument* pDoc = GetActiveDocument(); ASSERT(pDoc != NULL);
 if (pDoc->IsKindOf(RUNTIME_CLASS(CScriptDoc))) 
   if (theApp.CurrentTask&EDIT_KB) {
     CScriptDoc* pScrD; pScrD = (CScriptDoc*)pDoc; pScrD ->KBClose(TRUE);
     CMDIChildWnd::OnClose();
   }

}

//////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitViewBMFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitViewBMFrame)
    ON_WM_CLOSE()
    ON_COMMAND(ID_VIEW_EXIT, OnViewExit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitViewBMFrame

// Create a splitter window which splits an output text view and an input view
//                |  CBrTitle  (CScrollView)
//  CTreeView     |------------------
//  (CScrollView) |  CBVView   (CBrView)
//                |------------------
//                |  CBMView   (CBrView)
//                |------------------
//                |  CWordView (CBrView)
//---------------------------------------------------------------

IMPLEMENT_DYNCREATE(CSplitViewBMFrame, CMDIChildWnd)

CSplitViewBMFrame::CSplitViewBMFrame()   { }
CSplitViewBMFrame::~CSplitViewBMFrame()  { }

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitViewBMFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{   if (!m_wndSplitter.CreateStatic(this, 2, 1,WS_CHILD | WS_VISIBLE | WS_BORDER 
        | WS_VSCROLL | WS_HSCROLL))
      { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetRowInfo(0,28,16);
  m_wndSplitter.SetRowInfo(1,300,80);

  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CBrTitle), CSize(0,28), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CBM_View), CSize(0,154), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(1,0)); // activate the input view
  return TRUE;
}

//----------------------------------------------------------------------PreCreateWindow
BOOL CSplitViewBMFrame::PreCreateWindow( CREATESTRUCT& cs )
{  cs.style &= ~(LONG)FWS_ADDTOTITLE; cs.cy=600; cs.cx=640; cs.x=180; cs.y=24;
   return CMDIChildWnd::PreCreateWindow(cs);
}

//----------------------------------------------------------------------OnClose
void CSplitViewBMFrame::OnClose()
{ CScriptDoc*  pDoc = (CScriptDoc*)GetActiveDocument(); ASSERT(pDoc != NULL);
  if (theApp.CurrentTask & GEN_DB) { 
        pDoc ->FromMatrDB(pDoc ->m_Matr); 
        theApp.CurrentTask &= ~GEN_DB; pDoc ->DBSave(); 
  }
  else                             { pDoc ->FromMatr(pDoc ->m_Matr); pDoc ->KBSave(); }
  pDoc ->UpdateAllViews(NULL);
  CMDIChildWnd::OnClose();
}

//----------------------------------------------------------------------OnViewExit
void CSplitViewBMFrame::OnViewExit() { OnClose(); }




///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(CSplitExplanFrame, CMDIChildWnd)
    //{{AFX_MSG_MAP(CSplitExplanFrame)
    ON_WM_CLOSE()
    ON_COMMAND(ID_VIEW_EXPLAN_EXIT, OnViewExplanExit)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//---------------------------------------------------------------
// CSplitExplanFrame

// Create a splitter window which splits an output text view and an input view
//               
//  CExplanHeadView (CBrView)
//---------------------------------------------------------------
//  CExplanView     (CBrView)
//---------------------------------------------------------------


IMPLEMENT_DYNCREATE(CSplitExplanFrame, CMDIChildWnd)

CSplitExplanFrame::CSplitExplanFrame()   { }
CSplitExplanFrame::~CSplitExplanFrame()  { }  //WM_CANCELMODE

//--------------------------------------------------------------------OnCreateClient
BOOL CSplitExplanFrame::OnCreateClient(LPCREATESTRUCT, CCreateContext* pContext)
{ 
  if (!m_wndSplitter.CreateStatic(this, 2, 1,WS_CHILD | WS_VISIBLE | WS_BORDER| WS_HSCROLL))  // create a splitter with 1 row, 2 columns
     { TRACE("Failed to CreateStaticSplitter\n"); return FALSE; }
  m_wndSplitter.SetRowInfo(0,200,40);
  m_wndSplitter.SetRowInfo(1,220,120);
  

  if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CExplanView), CSize( 0,200), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  if (!m_wndSplitter.CreateView(1, 0, RUNTIME_CLASS(CExplanStepView), CSize( 0,220), pContext))
    { TRACE("Failed to create pane\n"); return FALSE; }
  SetActiveView((CView*)m_wndSplitter.GetPane(1,0)); // activate the input view
  return TRUE;
}

//--------------------------------------------------------------------PreCreateWindow
BOOL CSplitExplanFrame::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE;  cs.cy=600;  cs.cx=800; cs.y=20;  cs.x=0;
  return CMDIChildWnd::PreCreateWindow(cs);
}

//--------------------------------------------------------------------OnClose
void CSplitExplanFrame::OnClose()
{ theApp.CurrentTask&=~(EXPLAN); CMDIChildWnd::OnClose(); }


void CSplitExplanFrame::OnViewExplanExit()   { OnClose(); }
                                                                             
                                                                             /////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////// CIndWnd

IMPLEMENT_DYNCREATE(CIndWnd, CMDIChildWnd)

CIndWnd::CIndWnd(){}

CIndWnd::~CIndWnd(){}


BEGIN_MESSAGE_MAP(CIndWnd, CMDIChildWnd)
    //{{AFX_MSG_MAP(CIndWnd)
        // NOTE - the ClassWizard will add and remove mapping macros here.
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CIndWnd message handlers
//--------------------------------------------------------------------PreCreateWindow
BOOL CIndWnd::PreCreateWindow( CREATESTRUCT& cs )
{ cs.style &= ~(LONG)FWS_ADDTOTITLE;  cs.cy=400;  cs.cx=400; cs.y=50;  cs.x=310;
  return CMDIChildWnd::PreCreateWindow(cs);
}


