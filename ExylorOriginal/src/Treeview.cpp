// TreeView.cpp : implementation of the CTreeView class / CTrRegView class
// 17.05.2007 ------------------------------------------
//------------------------------------------------------
#include "stdafx.h"
#include "Exsylor.h"
#include "mainfrm.h"
#include "scrdoc.h"
#include "brview.h"
#include "trbzview.h"
#include "treeview.h"
#include "bmview.h"

#include <stdlib.h>
#include <limits.h> // for INT_MAX
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeView

IMPLEMENT_DYNCREATE(CTreeView, CTrBzView)

BEGIN_MESSAGE_MAP(CTreeView, CTrBzView)
  //{{AFX_MSG_MAP(CTreeView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
    // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeView construction/destruction

CTreeView::CTreeView()  { m_nPrevRowCount=0; }

CTreeView::~CTreeView() { }

/////////////////////////////////////////////////////////////////////////////
// CTreeView drawing

//----------------------------------------------------------
void CTreeView::OnUpdate(CView* Sender, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = GetDocument();
 if (pHint!=NULL && theApp.m_nActiveFrame!=DBVIEW) return;
 if (LOWORD(lHint)>0 && pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) {
   int nRow = LOWORD(lHint)-1; UpdateRow(nRow);
 }
 else if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CSBlock))) return;
 else { Invalidate(); }
}

//------------------------------------------------------------
void CTreeView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=DBVIEW) {  //  change toolbars if it's nessesary
      if (theApp.CurrentTask&NEW_SAMPLE) pFrameWnd->ViewDB();
      else                               pFrameWnd->ViewDBEdit();
      theApp.m_nActiveFrame = DBVIEW;
    }
  }
}

//------------------------------------------------------------
void CTreeView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);
  nRowHeight = tm.tmHeight+2; // line of text
  nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
}

//------------------------------------------------------------
int CTreeView::GetActiveRow()
{ CScriptDoc* pDoc = GetDocument();
  int w,j;
 w = pDoc->m_TreeRow.GetAt(pDoc->m_ActDRow);
 j = LOBYTE(w);
 if (j == 0xff) pDoc->m_ActDRow++;
 return (pDoc->m_ActDRow);
}

//------------------------------------------------------------
int CTreeView::GetRowCount()
{   CScriptDoc* pDoc = GetDocument();
    return (pDoc->m_nValues+pDoc->m_nAttributes);
}
//------------------------------------------------------------
void CTreeView::ChangeSelectionNextRow(BOOL bNext)
{ CScriptDoc* pDoc = GetDocument();
  pDoc->ChangeSelectionNextRowNo(bNext,pDoc->m_ActDRow);
}

//------------------------------------------------------------
void CTreeView::ChangeSelectionToRow(int nRow)
{ CScriptDoc* pDoc = GetDocument();
  pDoc->ChangeSelectionToRowNo(nRow,pDoc->m_ActDRow);
}

//------------------------------------------------------------
void CTreeView::OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected)
{ // Prepare for highlighting or un-highlighting the node, depending on whether it is the
  // currently selected wpl or not.  And paint the background (behind the text) accordingly.
 CBrush brushBackground;   // save colors for drawing selected item on the screen
 COLORREF crNewBackG;
 COLORREF crNewText;
 COLORREF crOldText = 0;
 COLORREF crOldBackground = 0;
 COLORREF crGreen = RGB(0,128,0);
 COLORREF crDark = RGB(128,128,128);
 COLORREF crRed = RGB(128,0,0);
 COLORREF crGr = RGB(0,128,0);
 COLORREF crWhite = RGB(255,255,255);

 CScriptDoc* pDoc = GetDocument();
 int j,k,r;                        // Get the data for the specific node.
 CString W;
 WORD w;
 CkAttr* pAttr;

 w = pDoc->m_TreeRow.GetAt(nRow);
 j = LOBYTE(w);
 k = HIBYTE(w);
 pAttr = pDoc->m_pAttrObj.GetAt(k);

   if (!pDC->IsPrinting()) {
     if (bSelected) {
       if (j == 0xff) {
         crNewBackG = ::GetSysColor(COLOR_HIGHLIGHT);
         crNewText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
       }
       else {
         crNewText = crWhite;
         if (pAttr->m_DFlag.GetBitAt(j)) crNewBackG = crGr;
         else                            crNewBackG = crRed;
       }
     }
     else {
       crNewBackG =::GetSysColor(COLOR_WINDOW);
       if (j == 0xff) crNewText = ::GetSysColor(COLOR_WINDOWTEXT);
       else
         if (pAttr->m_DFlag.GetBitAt(j)) crNewText = crGreen;
         else                         crNewText =  crDark;
     }
     brushBackground.CreateSolidBrush(crNewBackG);
     crOldBackground = pDC->SetBkColor(crNewBackG);
     crOldText = pDC->SetTextColor(crNewText);
     CRect rectSelection;
     pDC->GetClipBox(&rectSelection);
     rectSelection.top = y;
     if (j != 0xff)  // Atrib
       rectSelection.left +=93;
     rectSelection.bottom = y + m_nRowHeight;
     pDC->FillRect(&rectSelection, &brushBackground);
   }
   if (j == 0xff) { // Atrib
     pDC->TextOut(20, y+2, pAttr->m_sTitle); Draw(pDC,3,0,y);
   }
   else {                  // Value
     W = pAttr->m_ValNames.GetAt(j);
     r = pAttr->m_DFlag.GetBitAt(j);
     pDC->TextOut(100, y+1, W);

     Draw(pDC,1+r,80,y);
     pDC->MoveTo(10,y+m_nRowHeight/2);    pDC->LineTo(80,y+m_nRowHeight/2);
     pDC->MoveTo(10,y-1);
     if ((pDoc->m_TreeRow.GetSize()==nRow+1) ||
          LOBYTE(pDoc->m_TreeRow.GetAt(nRow+1))== 0xff)  // End of Attrib
       pDC->LineTo(10,y+m_nRowHeight/2);
     else pDC->LineTo(10,y+m_nRowHeight);
   }
// Restore the DC.
  pDC->SetBkColor(crOldBackground);
  pDC->SetTextColor(crOldText);
}


/////////////////////////////////////////////////////////////////////////////
// CTreeView diagnostics

#ifdef _DEBUG
void CTreeView::AssertValid() const
{ CScrollView::AssertValid(); }
void CTreeView::Dump(CDumpContext& dc) const
{ CScrollView::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTreeView message handlers

//--------------------------------------------------------------
void CTreeView::ChangeColorRow(int nRow)
{ CScriptDoc* pDoc = GetDocument();
  int j,k,s;                        // Get the data for the specific node.
  WORD w;
  CkAttr* pAttr;
  w = pDoc->m_TreeRow.GetAt(GetActiveRow());
  j = LOBYTE(w);
  if (j == 0xff)  return; // Atrib
  k = HIBYTE(w);
  pAttr = pDoc->m_pAttrObj.GetAt(k);
  s = 1- pAttr->m_DFlag.GetBitAt(j);
  pAttr->m_DFlag.SetBitAt(j,s);
  UpdateRow(nRow);
  pDoc->ForDefSmp();  // For wordview
  pDoc->UpdateAllViews(this,MAKELONG(nRow,0),pDoc);
}


//--------------------------------------------------------------
void CTreeView::NextView()
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  ASSERT(pDoc != NULL);
  pDoc->NextView(RUNTIME_CLASS(CBMEditView));
}

//--------------------------------------------------------------
void CTreeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  switch (nChar)  {
  case VK_RETURN: if (theApp.CurrentTask <=0) break;
                  if (theApp.CurrentTask&NEW_SAMPLE) GetDocument()->AddOneSmp();
                  else  if (theApp.CurrentTask&EDIT_DB) GetDocument()->WriteOneSmp();
                  break;

  case VK_SPACE: if (theApp.CurrentTask <=0) break;
                 ChangeColorRow(GetActiveRow());      break;
  case VK_TAB:   NextView(); break;
  case VK_HOME:
    if (GetActiveRow()!=0) {
      ChangeSelectionToRow(0);OnVScroll(SB_TOP,0,GetScrollBarCtrl(SB_VERT));
    }
    break;
  case VK_END:
    if (GetActiveRow()!=GetRowCount()-1) ChangeSelectionToRow(GetRowCount()-1); break;
  case VK_UP:
    if (GetActiveRow()!=0) ChangeSelectionNextRow(FALSE); break;
  case VK_DOWN:
    if (GetActiveRow()!=GetRowCount()-1) ChangeSelectionNextRow(TRUE);    break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,   0, GetScrollBarCtrl(SB_VERT));    break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));    break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

 //--------------------------------------------------------------
void CTreeView::OnLButtonDown(UINT, CPoint point)
{ CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  SetCapture();       // Capture the mouse until button up.
}

//--------------------------------------------------------------------
void CTreeView::OnMouseMove(UINT nFlags, CPoint point)
{
 if (GetCapture() != this) return; // If this window (view) didn't capture the mouse,
                                   // then the user isn't drawing in this window.
 CClientDC dc(this); OnPrepareDC(&dc); dc.DPtoLP(&point);
 CRect rect(point, CSize(1,1));
 int nFirstRow, nLastRow;
 RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
 if (nFirstRow < 0) nFirstRow=0;
 if (nFirstRow!=m_nPrevSelectedRow)
   if (nFirstRow <= (GetRowCount() - 1)) ChangeSelectionToRow(nFirstRow);
}

//--------------------------------------------------------
void CTreeView::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop();
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  ChangeColorRow(nFirstRow);
}

//****************************************************************************
// Drawing one tools button
//****************************************************************************
void Draw(CDC* pDC,int j0,int x, int y)
{ CDC pM;
  CBitmap pB;
  BITMAP bm;
  if (theApp.CurrentTask<=0) return;
  pM.CreateCompatibleDC(pDC);
  pB.LoadBitmap(MAKEINTRESOURCE(IDB_BITMAP1+j0));
  pB.GetObject(sizeof(BITMAP), &bm);
  CBitmap* pOldBitmap = pM.SelectObject((CBitmap *)&pB);
  pDC->BitBlt(x+2,y+1,bm.bmWidth, bm.bmHeight,&pM, 0, 0, SRCCOPY);
  pM.SelectObject((CBitmap *)pOldBitmap);
  pB.DeleteObject();
  pM.DeleteDC();
}

//---------------------------------------------------------------------



/////////////////////////////////////////////////////////////////////////////
// CTrRegView

IMPLEMENT_DYNCREATE(CTrRegView, CTrBzView)

BEGIN_MESSAGE_MAP(CTrRegView, CTrBzView)
  //{{AFX_MSG_MAP(CTrRegView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
    // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrRegView construction/destruction

CTrRegView::CTrRegView()  { m_nPrevRowCount=0; }

CTrRegView::~CTrRegView() { }

/////////////////////////////////////////////////////////////////////////////
// CTrRegView drawing

//----------------------------------------------------------
void CTrRegView::OnUpdate(CView* Sender, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = GetDocument();
 if (pHint!=NULL && theApp.m_nActiveFrame!=KBVIEW) return;
 if (LOWORD(lHint)>0 && pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) {
   int nRow = LOWORD(lHint)-1; UpdateRow(nRow);
 }
 else if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CSBlock))) return;
      else { Invalidate(); }
}

//------------------------------------------------------------
void CTrRegView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=KBVIEW) {  //  change toolbars if it's nessesary
      if (theApp.CurrentTask&NEW_REGUL)  pFrameWnd->ViewKB();
      else                               pFrameWnd->ViewKBEdit();
      theApp.m_nActiveFrame = KBVIEW;
    }
  }
}

//------------------------------------------------------------
void CTrRegView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);
  nRowHeight = tm.tmHeight+2; // line of text
  nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
}

//------------------------------------------------------------
int CTrRegView::GetActiveRow()
{ CScriptDoc* pDoc = GetDocument();
  int w,j;
 w = pDoc->m_TreeRow.GetAt(pDoc->m_ActKRow);
 j = LOBYTE(w);
 if (j == 0xff) pDoc->m_ActKRow++;
 return (pDoc->m_ActKRow);
}
 
//------------------------------------------------------------
int CTrRegView::GetRowCount()
{   CScriptDoc* pDoc = GetDocument();
    return (pDoc->m_nValues+pDoc->m_nAttributes);
}
 
//------------------------------------------------------------
void CTrRegView::ChangeSelectionNextRow(BOOL bNext)
{ CScriptDoc* pDoc = GetDocument();
  pDoc->ChangeSelectionNextRowNo(bNext,pDoc->m_ActKRow);
}

//------------------------------------------------------------
void CTrRegView::ChangeSelectionToRow(int nRow)
{ CScriptDoc* pDoc = GetDocument(); 
  pDoc->ChangeSelectionToRowNo(nRow,pDoc->m_ActKRow);
}

//------------------------------------------------------------
void CTrRegView::OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected)
{
 CBrush brushBackground;   // save colors for drawing selected item on the screen
 COLORREF crNewBackG;
 COLORREF crNewText;
 COLORREF crOldText = 0;
 COLORREF crOldBackground = 0;
 COLORREF crGreen = RGB(0,128,0);
 COLORREF crDark = RGB(128,128,128);
 COLORREF crRed = RGB(128,0,0);
 COLORREF crGr = RGB(0,128,0);
 COLORREF crWhite = RGB(255,255,255);

 CScriptDoc* pDoc = GetDocument();
 int j,k,r;                        // Get the data for the specific node.
 CString W;
 WORD w;
 CkAttr* pAttr;

 w = pDoc->m_TreeRow.GetAt(nRow);
 j = LOBYTE(w);
 k = HIBYTE(w);
 pAttr = pDoc->m_pAttrObj.GetAt(k);

   if (!pDC->IsPrinting()) {
     if (bSelected) {
       if (j == 0xff) {
         crNewBackG = ::GetSysColor(COLOR_HIGHLIGHT);
         crNewText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
       }
       else {
         crNewText = crWhite;
         if (pAttr->m_KifFlag.GetBitAt(j) || 
             pAttr->m_KthenFlag.GetBitAt(j)) crNewBackG = crGr;
         else                                crNewBackG = crRed;
       }
     }
     else {
       crNewBackG =::GetSysColor(COLOR_WINDOW);
       if (j == 0xff) crNewText = ::GetSysColor(COLOR_WINDOWTEXT);
       else
         if (pAttr->m_KifFlag.GetBitAt(j) || 
             pAttr->m_KthenFlag.GetBitAt(j)) crNewText = crGreen;
         else                                crNewText =  crDark;
     }
     brushBackground.CreateSolidBrush(crNewBackG);
     crOldBackground = pDC->SetBkColor(crNewBackG);
     crOldText = pDC->SetTextColor(crNewText);
     CRect rectSelection;
     pDC->GetClipBox(&rectSelection);
     rectSelection.top = y;
     if (j != 0xff)  // Atrib
       rectSelection.left +=93;
     rectSelection.bottom = y + m_nRowHeight;
     pDC->FillRect(&rectSelection, &brushBackground);
   }
   if (j == 0xff) { // Atrib
     pDC->TextOut(32, y+2, pAttr->m_sTitle);
     if (pDoc->ModeInput==FALSE)  Draw(pDC,10,0,y); else Draw(pDC,0,0,y);
   }
   else {                  // Value
     W = pAttr->m_ValNames.GetAt(j);
     pDC->TextOut(100, y+1, W);
     r = 7;
     if (pAttr->m_KifFlag.GetBitAt(j)) r+=2;
     else if (pAttr->m_KthenFlag.GetBitAt(j)) r++;
     Draw(pDC,r,80,y);
     
     pDC->MoveTo(16,y+m_nRowHeight/2);    pDC->LineTo(80,y+m_nRowHeight/2);
     pDC->MoveTo(16,y-1);
     if ((pDoc->m_TreeRow.GetSize()==nRow+1) ||
          LOBYTE(pDoc->m_TreeRow.GetAt(nRow+1))== 0xff)  // End of Attrib
       pDC->LineTo(16,y+m_nRowHeight/2);
     else pDC->LineTo(16,y+m_nRowHeight);
   }
// Restore the DC.
  pDC->SetBkColor(crOldBackground);
  pDC->SetTextColor(crOldText);
}


/////////////////////////////////////////////////////////////////////////////
// CTrRegView message handlers
//--------------------------------------------------------------
void CTrRegView::WriteReg()
{ CScriptDoc* pDoc = GetDocument();
  if (pDoc->ModeInput==FALSE)  {
    pDoc->ModeInput = TRUE; pDoc->ForDefReg();  // For wordregview
    ChangeSelectionToRow(1);
    pDoc->UpdateAllViews(NULL,NULL,&pDoc->m_pAttrObj);
  }
  else                         pDoc->AddOneReg();
}

//--------------------------------------------------------------
void CTrRegView::ChangeColorRow(int nRow)
{ CScriptDoc* pDoc = GetDocument();
  int j,k,i,i1,s;                        // Get the data for the specific node.
  WORD w;
  CkAttr* pAttr;
  w = pDoc->m_TreeRow.GetAt(GetActiveRow());
  j = LOBYTE(w);
  if (j == 0xff)  return; // Atrib
  k = HIBYTE(w);
  pAttr = pDoc->m_pAttrObj.GetAt(k);
  if (pDoc->ModeInput==FALSE) {              // Left part of production
    i = pAttr->m_KifFlag.CountBit();
    i1 = pAttr->m_KthenFlag.CountBit();
    if (i1) {      // Attribute was defined for right part
      pAttr->m_KthenFlag.Zero(); pAttr->m_KifFlag.SetBitAt(j,1);
    }
    else
      if (i) {
        s = 1-pAttr->m_KifFlag.GetBitAt(j);
        pAttr->m_KifFlag.SetBitAt(j,s);
        if (pAttr->m_KifFlag.CountBit()==(int)pDoc->m_DomVal[k]) {
          pAttr->m_KifFlag.SetBitAt(j,0); return;   // all values - false!!!
        }
      }
      else  pAttr->m_KifFlag.SetBitAt(j,1);   // First mark value for this attribute
  }
  else {                                     // Right part of production
    i = pAttr->m_KifFlag.CountBit(); i1 = pAttr->m_KthenFlag.CountBit();
    if (i) return; // Attribute was included in left part
    s = 1-pAttr->m_KthenFlag.GetBitAt(j);
    pAttr->m_KthenFlag.SetBitAt(j,s);
  }
  UpdateRow(nRow);
  pDoc->ForDefReg();  // For wordregview
  pDoc->UpdateAllViews(this,MAKELONG(nRow,0),pDoc);
}


//--------------------------------------------------------------
void CTrRegView::NextView()
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  ASSERT(pDoc != NULL);
  pDoc->NextView(RUNTIME_CLASS(CBMRegEditView));
}

//--------------------------------------------------------------
void CTrRegView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ CScriptDoc* pDoc = GetDocument();
  switch (nChar)  {
  case VK_BACK  : pDoc->NextPart(); break;
  case VK_RETURN: if (theApp.CurrentTask&NEW_REGUL) WriteReg();
                  break;

  case VK_SPACE:  if (theApp.m_nActiveFrame==KBVIEW) ChangeColorRow(GetActiveRow());
                 break;
  case VK_TAB:   NextView(); break;
  case VK_HOME:  if (GetActiveRow()!=0) {
                   ChangeSelectionToRow(0);OnVScroll(SB_TOP,0,GetScrollBarCtrl(SB_VERT));
                 }
                 break;
  case VK_END:   if (GetActiveRow()!=GetRowCount()-1)
                   ChangeSelectionToRow(GetRowCount()-1);
                 break;
  case VK_UP:    if (GetActiveRow()!=0) ChangeSelectionNextRow(FALSE); break;
  case VK_DOWN:  if (GetActiveRow()!=GetRowCount()-1) ChangeSelectionNextRow(TRUE); break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,   0, GetScrollBarCtrl(SB_VERT));    break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));    break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

 //--------------------------------------------------------------
void CTrRegView::OnLButtonDown(UINT, CPoint point)
{ CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  SetCapture();       // Capture the mouse until button up.
}

//--------------------------------------------------------------------
void CTrRegView::OnMouseMove(UINT nFlags, CPoint point)
{
 if (GetCapture() != this) return; // If this window (view) didn't capture the mouse,
                                   // then the user isn't drawing in this window.
 CClientDC dc(this); OnPrepareDC(&dc); dc.DPtoLP(&point);
 CRect rect(point, CSize(1,1));
 int nFirstRow, nLastRow;
 RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
 if (nFirstRow < 0) nFirstRow=0;
 if (nFirstRow!=m_nPrevSelectedRow)
   if (nFirstRow <= (GetRowCount() - 1)) ChangeSelectionToRow(nFirstRow);
}

//--------------------------------------------------------
void CTrRegView::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop();
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  ChangeColorRow(nFirstRow);
}





/////////////////////////////////////////////////////////////////////////////
// CTrObView
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CTrObView, CTrBzView)

BEGIN_MESSAGE_MAP(CTrObView, CTrBzView)
  //{{AFX_MSG_MAP(CTrObView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
    // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrObView construction/destruction

CTrObView::CTrObView()  { m_nPrevRowCount=0; }

CTrObView::~CTrObView() { }

/////////////////////////////////////////////////////////////////////////////
// CTrObView drawing

//----------------------------------------------------------
void CTrObView::OnUpdate(CView* Sender, LPARAM lHint, CObject* pHint)
{ CScriptDoc* pDoc = GetDocument();
 if (pHint!=NULL && theApp.m_nActiveFrame!=OBVIEW) return;
 if (LOWORD(lHint)>0 && pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) {
   int nRow = LOWORD(lHint)-1; UpdateRow(nRow);
 }
 else if (pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CSBlock))) return;
 else { Invalidate(); }
}

//------------------------------------------------------------
void CTrObView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=OBVIEW) {  //  change toolbars if it's nessesary
      if (theApp.CurrentTask&AIM) pFrameWnd->ViewRec();
      //else                           pFrameWnd->ViewDBEdit();
      theApp.m_nActiveFrame = OBVIEW;
    }
    
  }
}

//------------------------------------------------------------
void CTrObView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{  TEXTMETRIC tm;
  pDC->GetTextMetrics(&tm);
  nRowHeight = tm.tmHeight+2; // line of text
  nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
}

//------------------------------------------------------------
int CTrObView::GetActiveRow()
{ CScriptDoc* pDoc = GetDocument();
  int w,j;
 w = pDoc->m_TreeRow.GetAt(pDoc->m_ActDRow);
 j = LOBYTE(w);
 if (j == 0xff) pDoc->m_ActDRow++;
 return (pDoc->m_ActDRow);
}

//------------------------------------------------------------
int CTrObView::GetRowCount()
{   CScriptDoc* pDoc = GetDocument();
    return (pDoc->m_nValues+pDoc->m_nAttributes);
}
//------------------------------------------------------------
void CTrObView::ChangeSelectionNextRow(BOOL bNext)
{ CScriptDoc* pDoc = GetDocument();
  pDoc->ChangeSelectionNextRowNo(bNext,pDoc->m_ActDRow);
}

//------------------------------------------------------------
void CTrObView::ChangeSelectionToRow(int nRow)
{ CScriptDoc* pDoc = GetDocument();
  pDoc->ChangeSelectionToRowNo(nRow,pDoc->m_ActDRow);
}

//------------------------------------------------------------
void CTrObView::OnDrawRowWithSel(CDC* pDC, int nRow, int y, BOOL bSelected)
{
 CBrush brushBackground,brushBackground0;   // save colors for drawing selected item on the screen
 COLORREF crNewBackG;
 COLORREF crNewText;
 COLORREF crOldText = 0;
 COLORREF crOldBackground = 0;
 COLORREF crGreen = RGB(0,128,0);
 COLORREF crDark = RGB(128,128,128);
 COLORREF crRed = RGB(128,0,0);
 COLORREF crGr = RGB(0,128,0);
 COLORREF crWhite = RGB(255,255,255);

 CScriptDoc* pDoc = GetDocument();
 int j,k,r;                        // Get the data for the specific node.
 CString W;
 WORD w;
 CkAttr* pAttr;
 CRect rectSelection;
 pDC->GetClipBox(&rectSelection);
 rectSelection.top = y;// rectSelection.bottom = y + m_nRowHeight;

  if (pDoc->CheckObject) {
    brushBackground0.CreateSolidBrush(RGB(192,192,192));
    crOldBackground = pDC->SetBkColor(RGB(192,192,192));
    pDC->FillRect(&rectSelection, &brushBackground0);
  }
 rectSelection.bottom = y + m_nRowHeight;
 w = pDoc->m_TreeRow.GetAt(nRow);
 j = LOBYTE(w);
 k = HIBYTE(w);
 pAttr = pDoc->m_pAttrObj.GetAt(k);

   if (!pDC->IsPrinting()) {
     if (bSelected) {
       if (j == 0xff) {
         if (pDoc->CheckObject)  crNewBackG = RGB(192,192,192);
         else                    crNewBackG =::GetSysColor(COLOR_HIGHLIGHT);
         crNewText = ::GetSysColor(COLOR_HIGHLIGHTTEXT);
       }
       else {
         crNewText = crWhite;
         if (pAttr->m_DFlag.GetBitAt(j)) crNewBackG = crGr;
         else                            crNewBackG = crRed;
       }
     }
     else {
       if (pDoc->CheckObject)  crNewBackG = RGB(192,192,192);
       else crNewBackG = ::GetSysColor(COLOR_WINDOW);
       if (j == 0xff) crNewText = ::GetSysColor(COLOR_WINDOWTEXT);
       else
         if (pAttr->m_DFlag.GetBitAt(j)) crNewText = crGreen;
         else                            crNewText =  crDark;
     }
     brushBackground.CreateSolidBrush(crNewBackG);
     pDC->SetBkColor(crNewBackG);
     crOldText = pDC->SetTextColor(crNewText);

     if (j != 0xff) rectSelection.left +=93; // Atrib
     pDC->FillRect(&rectSelection, &brushBackground);
   }
   if (j == 0xff) { // Atrib
     pDC->TextOut(20, y+2, pAttr->m_sTitle); Draw(pDC,pDoc->CheckObject?13:5,0,y);
   }
   else {                  // Value
     W = pAttr->m_ValNames.GetAt(j);
     pDC->TextOut(110, y+1, W);     
     r = pAttr->m_DFlag.GetBitAt(j); if (pDoc->CheckObject) r+=3;
     Draw(pDC,11+r,80,y);
     pDC->MoveTo(10,y+m_nRowHeight/2);    pDC->LineTo(80,y+m_nRowHeight/2);
     pDC->MoveTo(10,y-1);
     if ((pDoc->m_TreeRow.GetSize()==nRow+1) ||
          LOBYTE(pDoc->m_TreeRow.GetAt(nRow+1))== 0xff)  // End of Attrib
       pDC->LineTo(10,y+m_nRowHeight/2);
     else pDC->LineTo(10,y+m_nRowHeight);
   }
// Restore the DC.
  pDC->SetBkColor(crOldBackground);
  pDC->SetTextColor(crOldText);
}
   

/////////////////////////////////////////////////////////////////////////////
// CTrObView diagnostics

#ifdef _DEBUG
void CTrObView::AssertValid() const
{ CScrollView::AssertValid(); }
void CTrObView::Dump(CDumpContext& dc) const
{ CScrollView::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTrObView message handlers

//--------------------------------------------------------------
void CTrObView::ChangeColorRow(int nRow)
{ CScriptDoc* pDoc = GetDocument();
  int j,k,s;                        // Get the data for the specific node.
  WORD w;
  CkAttr* pAttr;
  w = pDoc->m_TreeRow.GetAt(GetActiveRow());
  j = LOBYTE(w);
  if (j == 0xff)  return; // Atrib
  k = HIBYTE(w);
  pAttr = pDoc->m_pAttrObj.GetAt(k);
  s = 1- pAttr->m_DFlag.GetBitAt(j);
  pAttr->m_DFlag.SetBitAt(j,s);
  if (pAttr->m_DFlag.IsZero()) { pAttr->m_DFlag.SetBitAt(j,1); return; }
  UpdateRow(nRow);
  pDoc->ForDefSmp();  // For wordview
  pDoc->UpdateAllViews(this,MAKELONG(nRow,0),pDoc);
}

//--------------------------------------------------------------
void CTrObView::NextView()
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  ASSERT(pDoc != NULL);
  pDoc->NextView(RUNTIME_CLASS(CBMRegView));
}

//--------------------------------------------------------------
void CTrObView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ if (theApp.CurrentTask&AIM_VAL) return;
  CScriptDoc* pDoc = GetDocument();
  switch (nChar)  {
  case VK_SPACE: if (!pDoc->CheckObject) ChangeColorRow(GetActiveRow());      break;
  case VK_TAB:   NextView(); break;
  case VK_HOME:  if (GetActiveRow()!=0) {
                   ChangeSelectionToRow(0);OnVScroll(SB_TOP,0,GetScrollBarCtrl(SB_VERT));
                 }
                 break;
  case VK_END:
    if (GetActiveRow()!=GetRowCount()-1) ChangeSelectionToRow(GetRowCount()-1); break;
  case VK_UP:
    if (GetActiveRow()!=0) ChangeSelectionNextRow(FALSE); break;
  case VK_DOWN:
    if (GetActiveRow()!=GetRowCount()-1) ChangeSelectionNextRow(TRUE);    break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,   0, GetScrollBarCtrl(SB_VERT));    break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN, 0, GetScrollBarCtrl(SB_VERT));    break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

 //--------------------------------------------------------------
void CTrObView::OnLButtonDown(UINT, CPoint point)
{ if (theApp.CurrentTask&AIM_VAL) return;
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  SetCapture();       // Capture the mouse until button up.
}

//--------------------------------------------------------------------
void CTrObView::OnMouseMove(UINT nFlags, CPoint point)
{
 if (GetCapture() != this) return; // If this window (view) didn't capture the mouse,
                                   // then the user isn't drawing in this window.
 CClientDC dc(this); OnPrepareDC(&dc); dc.DPtoLP(&point);
 CRect rect(point, CSize(1,1));
 int nFirstRow, nLastRow;
 RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
 if (nFirstRow < 0) nFirstRow=0;
 if (nFirstRow!=m_nPrevSelectedRow)
   if (nFirstRow <= (GetRowCount() - 1)) ChangeSelectionToRow(nFirstRow);
}

//--------------------------------------------------------
void CTrObView::OnRButtonDown(UINT nFlags, CPoint point)
{ CScriptDoc* pDoc = GetDocument();
  GetParentFrame()->BringWindowToTop();
  if (theApp.CurrentTask&AIM_VAL) return;
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
  if (!pDoc->CheckObject) ChangeColorRow(nFirstRow);
}

