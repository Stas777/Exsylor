// scriptvw.cpp : implementation file
// 17.05.2007

#include "stdafx.h"
#include "Exsylor.h"
#include "mainfrm.h"
#include "scrdoc.h"
#include "scriptvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptView

IMPLEMENT_DYNCREATE(CScriptView, CFormView)

//---------------------------------------------------------------CScriptView
CScriptView::CScriptView()
    : CFormView(CScriptView::IDD)
{
    //{{AFX_DATA_INIT(CScriptView)
    m_nAttr = 0;
    m_nDB = 0;
    m_nKB = 0;
    m_nVal = 0;
    m_NameDB = "";
    m_NameKB = "";
    m_nRegul = 0;
    m_nSampl = 0;
    //}}AFX_DATA_INIT
}

//--------------------------------------------------------------~CScriptView
CScriptView::~CScriptView() { }

//--------------------------------------------------------------OnUpdate
void CScriptView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();

  m_nAttr = pDoc-> m_nAttributes;
  m_nDB = pDoc->m_DBMap.GetCount();
  m_nKB = pDoc->m_KBMap.GetCount();
  m_nVal = pDoc-> m_nValues;
  m_NameDB = pDoc->m_ActDB;
  m_NameKB = pDoc->m_ActKB;
  m_nRegul = pDoc->m_KBMap.GetElemForActive(m_NameKB);
  m_nSampl = pDoc->m_DBMap.GetElemForActive(m_NameDB);
  UpdateData(FALSE); Invalidate();
}

//------------------------------------------------------------
void CScriptView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=MODVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewMod(); theApp.m_nActiveFrame = MODVIEW;
    }
  }
}


//--------------------------------------------------------------DoDataExchange
void CScriptView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CScriptView)
    DDX_Text(pDX, IDC_NUM_ATTRIBE, m_nAttr);
    DDV_MinMaxInt(pDX, m_nAttr, 0, 63);
    DDX_Text(pDX, IDC_NUM_DB, m_nDB);
    DDV_MinMaxInt(pDX, m_nDB, 0, 63);
    DDX_Text(pDX, IDC_NUM_KB, m_nKB);
    DDV_MinMaxInt(pDX, m_nKB, 0, 63);
    DDX_Text(pDX, IDC_NUM_VALUE, m_nVal);
    DDV_MinMaxInt(pDX, m_nVal, 0, 63);
    DDX_Text(pDX, IDC_NAME_DB, m_NameDB);
    DDX_Text(pDX, IDC_NAME_KB, m_NameKB);
    DDX_Text(pDX, IDC_NUM_VALUE2, m_nRegul);
    DDX_Text(pDX, IDC_NUM_VALUE3, m_nSampl);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptView, CFormView)
    //{{AFX_MSG_MAP(CScriptView)
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptView message handlers

void CScriptView::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop(); 
  CFormView::OnRButtonDown(nFlags, point); }


/////////////////////////////////////////////////////////////////////////////
// CRecogScriptView

IMPLEMENT_DYNCREATE(CRecogScriptView, CFormView)

CRecogScriptView::CRecogScriptView() : CFormView(CRecogScriptView::IDD)
{
    //{{AFX_DATA_INIT(CRecogScriptView)
    m_NameKB = "";
    m_nAttr = 0;
    m_nVal = 0;
    m_nRegul = 0;
    //}}AFX_DATA_INIT
}

CRecogScriptView::~CRecogScriptView() { }

//--------------------------------------------------------------OnUpdate
void CRecogScriptView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
 if (pV==NULL && lHint==0L && pHint== NULL) {
   m_nAttr = pDoc-> m_nAttributes; m_nVal = pDoc-> m_nValues;
   m_NameKB = pDoc->m_ActKB;
   m_nRegul = pDoc->m_KBMap.GetElemForActive(m_NameKB);
 }
 UpdateData(FALSE); Invalidate();
}

//------------------------------------------------------------
void CRecogScriptView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=OBVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewRec(); theApp.m_nActiveFrame = OBVIEW;
    }
  }
}

//------------------------------------------------------------
void CRecogScriptView::DoDataExchange(CDataExchange* pDX)
{
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CRecogScriptView)
    DDX_Text(pDX, IDC_NAME_KB, m_NameKB);
    DDX_Text(pDX, IDC_NAME_MOD, m_NameMod);
    DDX_Text(pDX, IDC_NUM_ATTRIBE, m_nAttr);
    DDV_MinMaxInt(pDX, m_nAttr, 0, 63);
    DDX_Text(pDX, IDC_NUM_VALUE, m_nVal);
    DDV_MinMaxInt(pDX, m_nVal, 0, 63);
    DDX_Text(pDX, IDC_NUM_VALUE2, m_nRegul);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRecogScriptView, CFormView)
    //{{AFX_MSG_MAP(CRecogScriptView)
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////

void CRecogScriptView::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop(); CFormView::OnRButtonDown(nFlags, point); }