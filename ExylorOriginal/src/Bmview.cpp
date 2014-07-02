// 17.05.2007 -------------------------------------------
//-------------------------------------------------------
#include "stdafx.h"
#include "Exsylor.h"
#include "scrdoc.h"
#include "mainfrm.h"
#include "brview.h"
#include "bmview.h"
#include "trbzview.h"
#include "treeview.h"

#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern void Draw(CDC* pDC,int j0,int x, int y);

IMPLEMENT_DYNCREATE(CBMView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBMView
CBMView::CBMView() { }

BEGIN_MESSAGE_MAP(CBMView, CBrView)
    //{{AFX_MSG_MAP(CBMView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CBMView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{ if (pHint!=NULL && theApp.m_nActiveFrame!=DBVIEW) return;
 if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) return;
 UpdateScrollSizes(); Invalidate();
 if (theApp.m_nActiveFrame==DBVIEW) {
   if (theApp.CurrentTask&NEW_SAMPLE) OnVScroll(SB_BOTTOM,0,GetScrollBarCtrl(SB_VERT));
 }
}

//------------------------------------------------------------
void CBMView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=DBVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewDB(); theApp.m_nActiveFrame = DBVIEW;
    }
  }
}

//------------------------------------------------------------
int CBMView::GetRowCount()
{ CScriptDoc* pDoc = GetDocument();  return (pDoc->m_pSamples.GetSize()); }

//------------------------------------------------------------
void CBMView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crNewText = RGB(128,0,0), crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int width,i,Pos,n;
  char buf[128];
  CSize  cs;
  CSample* pSmp;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();

  pDC->GetTextMetrics(&tm);
  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);

  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть

  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y;  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(crNewText);      // Красный текст
  PutNumber(pDC,nRow,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
  pSmp = pDoc->m_pSamples.GetAt(nRow);

  for (i=0; i<(int)pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++)
      buf[n]= pSmp->m_Values.GetAt(pDoc->m_DomAdr[i]+n) ? '1':Symbol0;
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(crNewText);      // Красный текст
  }
 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CBMEditView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBMEditView
CBMEditView::CBMEditView() { }

BEGIN_MESSAGE_MAP(CBMEditView, CBrView)
    //{{AFX_MSG_MAP(CBMEditView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CBMEditView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{ if (pHint!=NULL && theApp.m_nActiveFrame!=DBVIEW) return;
 if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) return;
 else if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CSBlock))) {
        int nSmp = LOWORD(lHint)-1;
        if (theApp.m_nActiveFrame==DBVIEW) {
          UpdateRow(nSmp);
        }
      }
 else { UpdateScrollSizes(); Invalidate(); }
}

//------------------------------------------------------------
void CBMEditView::OnInitialUpdate()
{ m_nPrevRowCount=GetRowCount(); m_nPrevSelectedRow=GetActSmp(); UpdateScrollSizes(); }

//------------------------------------------------------------
void CBMEditView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=DBVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewDBEdit(); theApp.m_nActiveFrame = DBVIEW;
    }
  }
}

//------------------------------------------------------------
int CBMEditView::GetRowCount()
{ CScriptDoc* pDoc = GetDocument(); return (pDoc->m_pSamples.GetSize()); }

//------------------------------------------------------------
int CBMEditView::GetActSmp()
{ CScriptDoc* pDoc = GetDocument(); return (pDoc->m_ActSmp); }

//------------------------------------------------------------
void CBMEditView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crNewText = RGB(128,0,0), crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int width,i,Pos,n;
  char buf[128];
  CSize  cs;
  CSample* pSmp;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();

  pDC->GetTextMetrics(&tm);
  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть

  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y;  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(crNewText);      // Красный текст

  if (pDoc->m_ActSmp==nRow)  { Draw(pDC,6,23, y); }  // Active
  PutNumber(pDC,nRow,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);

  pSmp = pDoc->m_pSamples.GetAt(nRow);
  for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++)
      buf[n]= pSmp->m_Values.GetAt(pDoc->m_DomAdr[i]+n) ? '1':Symbol0;
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(crNewText);      // Красный текст
  }
 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}

//---------------------------------------------------------------------
void CBMEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  switch (nChar)  {
  case VK_TAB:   NextView(); break;
  case VK_HOME:  OnVScroll(SB_TOP,      0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_END:   OnVScroll(SB_BOTTOM,   0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_UP:    if (GetActSmp()!=0) ChangeSelectionNextRow(FALSE); break;
  case VK_DOWN:  if (GetActSmp()<GetRowCount()-1) ChangeSelectionNextRow(TRUE); break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,  0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN,0, GetScrollBarCtrl(SB_VERT)); break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

//--------------------------------------------------------------
void CBMEditView::ChangeSelectionNextRow(BOOL bNext)
{ GetDocument()->ChangeSelectionNextSmpNo(bNext); }

//--------------------------------------------------------------
void CBMEditView::ChangeSelectionToRow(int nRow)
{ GetDocument()->ChangeSelectionToSmpNo(nRow); }

//--------------------------------------------------------------
void CBMEditView::UpdateRow(int nInvalidRow)
{ int nRowCount = GetRowCount();
 if (nRowCount != m_nPrevRowCount) { UpdateScrollSizes(); m_nPrevRowCount = nRowCount; }
 CClientDC dc(this);
 OnPrepareDC(&dc);

 int nFirstRow, nLastRow;
 CRect rectClient;
 GetClientRect(&rectClient);
 dc.DPtoLP(&rectClient);
 RectLPtoRowRange(rectClient, nFirstRow, nLastRow, FALSE);

 POINT pt;
 pt.x = 0;
 BOOL bNeedToScroll = TRUE;
 if (nInvalidRow < nFirstRow) pt.y = RowToYPos(nInvalidRow);
 else
   if (nInvalidRow > nLastRow) pt.y=max(0,RowToYPos(nInvalidRow+1) - rectClient.Height());
   else bNeedToScroll = FALSE;
 if (bNeedToScroll) { ScrollToDevicePosition(pt); OnPrepareDC(&dc); }
 CRect rectInvalid = RowToWndRect(&dc, nInvalidRow);
 rectInvalid.left=23; rectInvalid.right=37;
 InvalidateRect(&rectInvalid);
 int nSelectedRow = GetActSmp();
 if (m_nPrevSelectedRow != nSelectedRow) {
   CRect rectOldSelection = RowToWndRect(&dc, m_nPrevSelectedRow);
   rectOldSelection.left=23; rectOldSelection.right=37;
   InvalidateRect(&rectOldSelection);
   m_nPrevSelectedRow = nSelectedRow;
 }
}

//--------------------------------------------------------------
void CBMEditView::OnLButtonDown(UINT nFlags, CPoint point)
{ if (!(theApp.CurrentTask & EDIT_DB)) return;
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
   CBrView::OnLButtonDown(nFlags, point);
}

//--------------------------------------------------------------
void CBMEditView::OnRButtonDown(UINT nFlags, CPoint point)
{ if (!(theApp.CurrentTask & EDIT_DB)) return;
  OnLButtonDown(nFlags, point);
  GetDocument()->ReadCurrentSmp();
  CBrView::OnRButtonDown(nFlags, point);
}

//--------------------------------------------------------------
void CBMEditView::NextView()
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  ASSERT(pDoc != NULL);
  pDoc->NextView(RUNTIME_CLASS(CTreeView));
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CBMRegView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBMRegView
CBMRegView::CBMRegView() { }

BEGIN_MESSAGE_MAP(CBMRegView, CBrView)
    //{{AFX_MSG_MAP(CBMRegView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CBrView
void CBMRegView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{ if (pHint!=NULL && theApp.m_nActiveFrame!=KBVIEW) return;
 if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) return;
 UpdateScrollSizes(); Invalidate();
 if (theApp.m_nActiveFrame==KBVIEW) {
   if (theApp.CurrentTask&NEW_REGUL) OnVScroll(SB_BOTTOM,0,GetScrollBarCtrl(SB_VERT));
 }
}

//------------------------------------------------------------
void CBMRegView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.CurrentTask&NEW_REGUL) {
      if (theApp.m_nActiveFrame!=KBVIEW) { 
        theApp.m_nActiveFrame = KBVIEW; pFrameWnd->ViewKB();
      }  
    }  
    else if (theApp.CurrentTask&OBJECT) { 
      if (theApp.m_nActiveFrame!=OBVIEW) { 
        theApp.m_nActiveFrame = OBVIEW; pFrameWnd->ViewRec();                
      }  
    }  
  }
}

//------------------------------------------------------------
int CBMRegView::GetRowCount()
{ CScriptDoc* pDoc = GetDocument();  return (pDoc->m_pReguls.GetSize()); }

//------------------------------------------------------------
void CBMRegView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crNewText = RGB(128,0,0), crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int width,i,Pos,n,k;
  char buf[128];
  CSize  cs;
  CSample* pReg;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();

  pDC->GetTextMetrics(&tm);
  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  if ( !pDoc->m_RowMask.IsEmpty() && pDoc->m_RowMask.GetBitAt(nRow))  crNewBack =RGB(224,224,0);
  else                            crNewBack =::GetSysColor(COLOR_WINDOW);

  brushBackground.CreateSolidBrush(crNewBack);

  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей
  Pos=40;
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y;  rectSelection.bottom = y + m_nRowHeight+2;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку
  crOldText = pDC->SetTextColor(crNewText);      // Красный текст
  PutNumber(pDC,nRow,y,FontOld,&FontNew,&lf);
  
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
  pReg = pDoc->m_pReguls.GetAt(nRow);

  for (i=0; i<(int)pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    for (k=n=0; n<(int)pDoc->m_DomVal[i]; n++)
      k |= pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n);
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++) {
      if (k&2)  buf[n]= (pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n)==0) ? '1':Symbol0;
      else      buf[n]= pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n)      ? '1':Symbol0;
    }
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(crNewText);      // Красный текст
  }
  pDC->SetBkColor(crOldBackground); pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}


/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CBMRegEditView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBMRegEditView
CBMRegEditView::CBMRegEditView() { }

BEGIN_MESSAGE_MAP(CBMRegEditView, CBrView)
    //{{AFX_MSG_MAP(CBMRegEditView)
    ON_WM_KEYDOWN()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CBMRegEditView::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{ if (pHint!=NULL && theApp.m_nActiveFrame!=KBVIEW) return;
 if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CScriptDoc))) return;
 else if ( pHint != NULL && pHint->IsKindOf(RUNTIME_CLASS(CSBlock))) {
        int nReg = LOWORD(lHint)-1;
        if (theApp.m_nActiveFrame==KBVIEW) {
          UpdateRow(nReg);
        }
      }
 else { UpdateScrollSizes(); Invalidate(); }
}

//------------------------------------------------------------
void CBMRegEditView::OnInitialUpdate()
{ m_nPrevRowCount=GetRowCount(); m_nPrevSelectedRow=GetActReg(); UpdateScrollSizes(); }

//------------------------------------------------------------
void CBMRegEditView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=KBVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewKBEdit(); theApp.m_nActiveFrame = KBVIEW;
    }
  }
}

//------------------------------------------------------------
int CBMRegEditView::GetRowCount() { return (GetDocument()->m_pReguls.GetSize()); }

//------------------------------------------------------------
int CBMRegEditView::GetActReg() { return (GetDocument()->m_ActReg); }

//------------------------------------------------------------
void CBMRegEditView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crNewText = RGB(128,0,0), crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int width,i,Pos,n,k;
  char buf[128];
  CSize  cs;
  CSample* pReg;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();

  pDC->GetTextMetrics(&tm);
  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть

  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y;  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(crNewText);      // Красный текст

  if (pDoc->m_ActReg==nRow)  { Draw(pDC,6,23, y); }  // Active
  PutNumber(pDC,nRow,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);

  pReg = pDoc->m_pReguls.GetAt(nRow);
  for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    for (k=n=0; n<(int)pDoc->m_DomVal[i]; n++)
      k |= pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n);
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++) {
      if (k&2)  buf[n]= (pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n)==0) ? '1':Symbol0;
      else      buf[n]= pReg->m_Values.GetAt(pDoc->m_DomAdr[i]+n)      ? '1':Symbol0;
    }
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(crNewText);      // Красный текст
  }
 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}

//---------------------------------------------------------------------
void CBMRegEditView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  switch (nChar)  {
  case VK_TAB:   NextView(); break;
  case VK_HOME:  OnVScroll(SB_TOP,      0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_END:   OnVScroll(SB_BOTTOM,   0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_UP:    if (GetActReg()!=0) ChangeSelectionNextRow(FALSE); break;
  case VK_DOWN:  if (GetActReg()<GetRowCount()-1) ChangeSelectionNextRow(TRUE); break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,  0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN,0, GetScrollBarCtrl(SB_VERT)); break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

//--------------------------------------------------------------
void CBMRegEditView::ChangeSelectionNextRow(BOOL bNext)
{ GetDocument()->ChangeSelectionNextRegNo(bNext); }

//--------------------------------------------------------------
void CBMRegEditView::ChangeSelectionToRow(int nRow)
{ GetDocument()->ChangeSelectionToRegNo(nRow); }

//--------------------------------------------------------------
void CBMRegEditView::UpdateRow(int nInvalidRow)
{ int nRowCount = GetRowCount();
 if (nRowCount != m_nPrevRowCount) { UpdateScrollSizes(); m_nPrevRowCount = nRowCount; }
 CClientDC dc(this);
 OnPrepareDC(&dc);

 int nFirstRow, nLastRow;
 CRect rectClient;
 GetClientRect(&rectClient);
 dc.DPtoLP(&rectClient);
 RectLPtoRowRange(rectClient, nFirstRow, nLastRow, FALSE);

 POINT pt;
 pt.x = 0;
 BOOL bNeedToScroll = TRUE;
 if (nInvalidRow < nFirstRow) pt.y = RowToYPos(nInvalidRow);
 else
   if (nInvalidRow > nLastRow) pt.y=max(0,RowToYPos(nInvalidRow+1) - rectClient.Height());
   else bNeedToScroll = FALSE;
 if (bNeedToScroll) { ScrollToDevicePosition(pt); OnPrepareDC(&dc); }
 CRect rectInvalid = RowToWndRect(&dc, nInvalidRow);
 rectInvalid.left=23; rectInvalid.right=37;
 InvalidateRect(&rectInvalid);
 int nSelectedRow = GetActReg();
 if (m_nPrevSelectedRow != nSelectedRow) {
   CRect rectOldSelection = RowToWndRect(&dc, m_nPrevSelectedRow);
   rectOldSelection.left=23; rectOldSelection.right=37;
   InvalidateRect(&rectOldSelection);
   m_nPrevSelectedRow = nSelectedRow;
 }
}

//--------------------------------------------------------------
void CBMRegEditView::OnLButtonDown(UINT nFlags, CPoint point)
{ if (!(theApp.CurrentTask & EDIT_KB)) return;
  CClientDC dc(this);  OnPrepareDC(&dc);  dc.DPtoLP(&point);
  CRect rect(point, CSize(1,1));
  int nFirstRow, nLastRow;
  RectLPtoRowRange(rect, nFirstRow, nLastRow, TRUE);
  if (nFirstRow <= (GetRowCount() - 1))   ChangeSelectionToRow(nFirstRow);
   CBrView::OnLButtonDown(nFlags, point);
}

//--------------------------------------------------------------
void CBMRegEditView::OnRButtonDown(UINT nFlags, CPoint point)
{ if (!(theApp.CurrentTask & EDIT_KB)) return;
  OnLButtonDown(nFlags, point);
  GetDocument()->ReadCurrentReg();
  CBrView::OnRButtonDown(nFlags, point);
}

//--------------------------------------------------------------
void CBMRegEditView::NextView()
{ CScriptDoc* pDoc = (CScriptDoc*)GetDocument();
  ASSERT(pDoc != NULL);
  pDoc->NextView(RUNTIME_CLASS(CTrRegView));
}

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////
//CBM_View
/////////////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CBM_View, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBM_View
CBM_View::CBM_View() { }

BEGIN_MESSAGE_MAP(CBM_View, CBrView)
    //{{AFX_MSG_MAP(CBM_View)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CBM_View::OnUpdate(CView*, LPARAM lHint, CObject* pHint)
{ if (pHint!=NULL) return;
  Invalidate();
}

//------------------------------------------------------------
void CBM_View::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=BMVIEW) {  //  change toolbars if it's nessesary
      pFrameWnd->ViewBM(); theApp.m_nActiveFrame = BMVIEW;
    }
  }
}

//------------------------------------------------------------
int CBM_View::GetRowCount()
{ CScriptDoc* pDoc = GetDocument();  return (pDoc->m_Matr.GetCountR()); }

//------------------------------------------------------------
void CBM_View::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crNewText = RGB(128,0,0), crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int width,i,Pos,n;
  char buf[128];
  CSize  cs;
  //CSample* pSmp;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();

  pDC->GetTextMetrics(&tm);
  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть

  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y;  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(crNewText);      // Красный текст
  PutNumber(pDC,nRow,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
  //pSmp = pDoc->m_pSamples.GetAt(nRow);

  for (i=0; i<(int)pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++)
      buf[n]= pDoc->m_Matr.GetBitAt(nRow,pDoc->m_DomAdr[i]+n) ? '1':Symbol0;
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(crNewText);      // Красный текст
  }
 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}


