// formind.cpp : implementation file
// 17.05.2007
//------------------------

#include "stdafx.h"
#include "Exsylor.h"
#include "mainfrm.h"
#include "scrdoc.h"
#include "formind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormInd

IMPLEMENT_DYNCREATE(CFormInd, CFormView)

CFormInd::CFormInd()
    : CFormView(CFormInd::IDD)
{ 
    //{{AFX_DATA_INIT(CFormInd)
    m_Num_Con = 1;
    m_LimRank = 1;
    m_LimProb = 1.;
    m_LimNum = 1;
    m_Rank = 1;
    m_Number = 1;
    m_Prob = 1.;
    //}}AFX_DATA_INIT
}

CFormInd::~CFormInd() {}  

//--------------------------------------------------------------OnUpdate
void CFormInd::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();

 if (pV==NULL && pHint== NULL && (lHint==0L || lHint==1213456789L)) {
    m_Num_Con = pDoc->Num_Con;
    m_LimRank = pDoc->Rank;
    m_LimProb = pDoc->Prob*100.;
    m_LimNum = pDoc->Numb;
    m_Rank = pDoc->FactRank;
    m_Number = pDoc->FactNum;
    m_Prob  =  pDoc->FactProb*100.;
   UpdateData(FALSE); /*Invalidate();*/ UpdateWindow() ;
 }
}

void CFormInd::DoDataExchange(CDataExchange* pDX)
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  CWnd* pWnd; pWnd = GetDlgItem(IDC_BUTTON1); 
  pDoc ->hTable = pWnd->m_hWnd;  
    CFormView::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CFormInd)
    DDX_Text(pDX, IDC_EDIT1, m_Num_Con);
    DDX_Text(pDX, IDC_EDIT2, m_LimRank);
    DDX_Text(pDX, IDC_EDIT3, m_LimProb);
    DDX_Text(pDX, IDC_EDIT4, m_LimNum);
    DDX_Text(pDX, IDC_EDIT5, m_Rank);
    DDX_Text(pDX, IDC_EDIT6, m_Number); 
    DDX_Text(pDX, IDC_EDIT7, m_Prob);
    DDV_MinMaxDouble(pDX, m_Prob, 0., 100.);
    //}}AFX_DATA_MAP
  
}

BEGIN_MESSAGE_MAP(CFormInd, CFormView)
    //{{AFX_MSG_MAP(CFormInd)
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormInd message handlers

void CFormInd::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop(); CFormView::OnRButtonDown(nFlags, point); }
