// ModView.cpp : implementation of the CModView class
// 17.05.2007
//---------------------------------------------------

#include "stdafx.h"
#include "Exsylor.h"
#include "mainfrm.h"
#include "scrdoc.h"
#include "brview.h"
#include "modview.h"


#include <stdlib.h>
#include <limits.h> // for INT_MAX
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModView

IMPLEMENT_DYNCREATE(CModView, CBrView)

BEGIN_MESSAGE_MAP(CModView, CBrView)
  //{{AFX_MSG_MAP(CModView)
    //}}AFX_MSG_MAP
  // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModView construction/destruction

CModView::CModView()
{
 m_nPrevRowCount=0;
 lf.lfPitchAndFamily = 18; lstrcpy(lf.lfFaceName,"Arial Cyr");
}

CModView::~CModView() { }

/////////////////////////////////////////////////////////////////////////////
// CModView drawing

//----------------------------------------------------------
void CModView::OnUpdate(CView* Sender, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = GetDocument();
  if (Sender==NULL && lHint==0L && pHint== NULL) {
    UpdateScrollSizes();Invalidate();
  }
}

//------------------------------------------------------------
void CModView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=MODVIEW) {   // change toolbars if it's nessesary
      pFrameWnd->ViewMod(); theApp.m_nActiveFrame = MODVIEW;
    }
  }
}

//------------------------------------------------------------
void CModView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{  TEXTMETRIC tm;
   CFont FontNew,*FontOld;
  pDC->GetTextMetrics(&tm);
  FontNew.CreateFontIndirect(&lf);  FontOld = pDC->SelectObject((CFont*)&FontNew);
  nRowHeight = tm.tmHeight; // line of text
  nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
  pDC->SelectObject((CFont*)FontOld);  FontNew.DeleteObject();
}

//------------------------------------------------------------
int CModView::GetRowCount()
{ CScriptDoc* pDoc = GetDocument();
  int Ret = max (pDoc->m_nValues+pDoc->m_nAttributes, 0);
  return Ret;
}

//------------------------------------------------------------
void CModView::OnDrawRow(CDC* pDC, int nRow, int y)
{
 CBrush brushBackground;   // save colors for drawing selected item on the screen
 COLORREF crNewBackG, crOldText, crOldBackground = 0;

 CFont FontNew,*FontOld;
 CScriptDoc* pDoc = GetDocument();
 int j,k;                        // Get the data for the specific node.
 CString W;
 WORD w;
 CkAttr* pAttr;

  w = pDoc->m_TreeRow.GetAt(nRow);  j = LOBYTE(w);  k = HIBYTE(w);
  pAttr = pDoc->m_pAttrObj.GetAt(k);

  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  if (!pDC->IsPrinting()) {
    crNewBackG =::GetSysColor(COLOR_WINDOW);
    brushBackground.CreateSolidBrush(crNewBackG);
    crOldBackground = pDC->SetBkColor(crNewBackG);
    CRect rectSelection;
    pDC->GetClipBox(&rectSelection);
    rectSelection.top = y;
    if (j != 0xff)  // Atrib
      rectSelection.left +=33;
    rectSelection.bottom = y + m_nRowHeight;
    pDC->FillRect(&rectSelection, &brushBackground);
  }

  if (j == 0xff) pDC->TextOut(2, y, pAttr->m_sTitle);    // Atrib
  else {                  // Value
    crOldText = pDC->SetTextColor(RGB(0,0,128));      // Blue
    W = pAttr->m_ValNames.GetAt(j);
    pDC->TextOut(40, y, W);
    pDC->SetTextColor(crOldText);
  }
// Restore the DC.
  pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
  pDC->SetBkColor(crOldBackground);
}

//--------------------------------------------------------------
void CModView::UpdateScrollSizes()
{ 
//  CScriptDoc* pDoc = GetDocument();
  CRect rectClient;    GetClientRect(&rectClient);
  CClientDC dc(this);  CalculateRowMetrics(&dc);
 CSize sizeTotal(0, m_nRowHeight * (min(GetRowCount(), LastViewableRow())));
 CSize sizePage(0, max(m_nRowHeight, ((rectClient.bottom/m_nRowHeight)-1)*m_nRowHeight));
 CSize sizeLine(0, m_nRowHeight);
 SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

