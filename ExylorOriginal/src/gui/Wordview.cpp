// wordview.cpp -------- CWordView , CWordRegView
// 17.05.2007
//-----------------------------------------------

#include "stdafx.h"
#include "Exsylor.h"
#include "mainfrm.h"
#include "scrdoc.h"
#include "brview.h"
#include "wordview.h"
#include "trbzview.h"
#include "treeview.h"
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CWordView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CWordView
CWordView::CWordView() { }

BEGIN_MESSAGE_MAP(CWordView, CBrView)
    //{{AFX_MSG_MAP(CWordView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CWordView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV!=NULL && theApp.m_nActiveFrame!=DBVIEW && theApp.m_nActiveFrame!=OBVIEW) return;
 if ((pV==NULL && lHint==0L && pHint== NULL) ||
     (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTreeView))) ||
     (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTrObView))) ||
     (pHint!= NULL  && pHint->IsKindOf(RUNTIME_CLASS(CkAttrArray))) )
   Invalidate();
}

//------------------------------------------------------------
void CWordView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.CurrentTask&NEW_SAMPLE) {
      if (theApp.m_nActiveFrame!=DBVIEW) { 
        theApp.m_nActiveFrame = DBVIEW; pFrameWnd->ViewDB();
      }  
    }  
    else if (theApp.CurrentTask&EDIT_DB) {
      if (theApp.m_nActiveFrame!=DBVIEW) {
        theApp.m_nActiveFrame = DBVIEW; pFrameWnd->ViewDBEdit();
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
int CWordView::GetRowCount()   { return (GetDocument()->m_sWordCount);}

//------------------------------------------------------------
void CWordView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int i,Pos,s;
  CString strD,strD1;
  CSize  cs;
  CStringArray * Word;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();
  if (pDoc->m_sWord.GetSize()==0) return;
  pDC->GetTextMetrics(&tm);
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть
  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);

  rectSelection.top = y;
  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(RGB(0,0,128));     // Синий текст

  Word = &pDoc->m_sWord;
  for (s=i=0; i<Word->GetSize(); i++) {
    strD = Word->GetAt(i);
    if (strD[0]=='Q' || strD[0]=='F')
      if (s==nRow) break;
      else s++;
  }
  Pos=3;
  do {
   switch ( strD[0]) {
   case 'F':
   case 'N': pDC->SetTextColor(RGB(128,0,0)); break;    // Red
   case 'Q': pDC->SetTextColor(RGB(0,0,128)); break;    // Blue
   case 'V': pDC->SetTextColor(RGB(0,128,0)); break;    // Blue
    default:  pDC->SetTextColor(crOldText);     break;  // Black
   }
   strD1 = strD.Right(strD.GetLength()-1);
   pDC->TextOut(Pos, y, strD1);
   cs  = pDC->GetTextExtent(strD1,strD1.GetLength());
   Pos+=cs.cx+3;
   i++;
   if (i>=Word->GetSize()) break;
   strD = Word->GetAt(i);
  } while (strD[0]!='Q' && strD[0]!='F');

 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}



IMPLEMENT_DYNCREATE(CWordRegView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CWordView
CWordRegView::CWordRegView() { }

BEGIN_MESSAGE_MAP(CWordRegView, CBrView)
    //{{AFX_MSG_MAP(CWordRegView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides CWordView
void CWordRegView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV!=NULL && theApp.m_nActiveFrame!=KBVIEW) return;
  if ((pV==NULL && lHint==0L && pHint== NULL) ||
      (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTrRegView))) ||
      (pHint!= NULL  && pHint->IsKindOf(RUNTIME_CLASS(CkAttrArray))) )
    Invalidate();
}

//------------------------------------------------------------
void CWordRegView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=KBVIEW) {  //  change toolbars if it's nessesary
      if (theApp.CurrentTask&NEW_REGUL) pFrameWnd->ViewKB();
      else                              pFrameWnd->ViewKBEdit();
      theApp.m_nActiveFrame = KBVIEW;
    }
  }
}

//------------------------------------------------------------
int CWordRegView::GetRowCount() { return (GetDocument()->m_sRegulWordCount); }

//------------------------------------------------------------
void CWordRegView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  int i,Pos,s;
  CString strD,strD1;
  CSize  cs;
  CStringArray * Word;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();
  if (pDoc->m_sRegulWord.GetSize()==0) return;
  pDC->GetTextMetrics(&tm);
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_WINDOW);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть
  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);

  rectSelection.top = y;
  rectSelection.bottom = y + m_nRowHeight;
  pDC->FillRect(&rectSelection, &brushBackground); // Всю строку сделать белой
  crOldText = pDC->SetTextColor(RGB(0,0,128));     // Синий текст

  Word = &pDoc->m_sRegulWord;
  for (s=i=0; i<Word->GetSize(); i++) {
    strD = Word->GetAt(i);
    if (strD[0]=='Q' || strD[0]=='F')
      if (s==nRow) break;
      else s++;
  }
  Pos=3;
  do {
   switch ( strD[0]) {
   case 'F':
   case 'N': pDC->SetTextColor(RGB(128,0,0)); break;    // Red
   case 'Q': pDC->SetTextColor(RGB(0,0,128)); break;    // Blue
   case 'V': pDC->SetTextColor(RGB(0,128,0)); break;    // Blue
   default:  pDC->SetTextColor(crOldText);    break;    // Black
   }
   strD1 = strD.Right(strD.GetLength()-1);
   pDC->TextOut(Pos, y, strD1);
   cs  = pDC->GetTextExtent(strD1,strD1.GetLength());
   Pos+=cs.cx+3;
   i++;
   if (i>=Word->GetSize()) break;
   strD = Word->GetAt(i);
  } while (strD[0]!='Q' && strD[0]!='F');

 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}


IMPLEMENT_DYNCREATE(CStageView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CStageView
CStageView::CStageView() { }

BEGIN_MESSAGE_MAP(CStageView, CBrView)
    //{{AFX_MSG_MAP(CStageView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CStageView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{
  if (pV==NULL && lHint==0L && pHint== NULL) Invalidate(); }

//------------------------------------------------------------
void CStageView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.CurrentTask&OBJECT)  
      if (theApp.m_nActiveFrame!=OBVIEW) { 
        theApp.m_nActiveFrame = OBVIEW; pFrameWnd->ViewRec();                
      }  
  }
}

//--------------------------------------------------------------
void CStageView::UpdateScrollSizes()
{
  CRect rectClient;
  GetClientRect(&rectClient); CClientDC dc(this); CalculateRowMetrics(&dc);
  CSize sizeTotal(0,m_nRowHeight * (min(GetRowCount(), LastViewableRow())));
  CSize sizePage(0, max(m_nRowHeight, ((rectClient.bottom/m_nRowHeight)-1)*m_nRowHeight));
  CSize sizeLine(0, m_nRowHeight);
  SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

//------------------------------------------------------------
int CStageView::GetRowCount()   { return 1;}

//------------------------------------------------------------
void CStageView::OnDrawRow(CDC* pDC, int nRow, int y)
{ CBrush brushBackground;
  COLORREF crNewBack,crOldText, crOldBackground = 0;
  CFont FontNew,*FontOld;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();
  if (pDoc->m_sStage.IsEmpty()) return;
  pDC->GetTextMetrics(&tm);
  lf.lfHeight = -14;
  lf.lfWeight = 700;
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  crNewBack =::GetSysColor(COLOR_ACTIVECAPTION);
  brushBackground.CreateSolidBrush(crNewBack);  //Белая кисть
  crOldBackground = pDC->SetBkColor(crNewBack); // Установить текущей белую
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  pDC->FillRect(&rectSelection, &brushBackground);
  crOldText = pDC->SetTextColor(::GetSysColor(COLOR_CAPTIONTEXT));
  pDC->TextOut(10, y, pDoc->m_sStage);
  pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
  pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}





IMPLEMENT_DYNCREATE(CExplanView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CExplanView
CExplanView::CExplanView() { }

BEGIN_MESSAGE_MAP(CExplanView, CBrView)
    //{{AFX_MSG_MAP(CExplanView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CExplanView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV==NULL && lHint==0L && pHint== NULL) Invalidate(); }

//------------------------------------------------------------
void CExplanView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=EXPLANVIEW) { 
      theApp.m_nActiveFrame = EXPLANVIEW; pFrameWnd->ViewExplan();                
    }  
  }
}

//------------------------------------------------------------
int CExplanView::GetRowCount()   { return (GetDocument()->m_sExplan.GetSize());}

//------------------------------------------------------------
void CExplanView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{ CBrView::GetRowWidthHeight(pDC, nRowWidth, nRowHeight);
  nRowHeight +=2;
}

//------------------------------------------------------------
void CExplanView::OnDrawRow(CDC* pDC, int nRow, int y)
{
  COLORREF crOldText;
  int Pos,s,k=0;
  CString strD,strD1;
  
  CSize  cs;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();
  pDC->GetTextMetrics(&tm);
  
  
  crOldText = pDC->SetTextColor(RGB(0,0,128));     // Синий текст
  strD = pDoc->m_sExplan.GetAt(nRow);
  Pos = 10;
  while (!strD.IsEmpty()) {
    s = strD.Find('^');
    if (s<0)    { pDC->TextOut(Pos, y, strD); break; }
    strD1 = strD.Left(s);
    strD = strD.Right(strD.GetLength()-s-1);
    pDC->TextOut(Pos, y, strD1);
    if (k) pDC->SetTextColor(RGB(0,0,128)); 
    else pDC->SetTextColor(RGB(128,0,0)); 
    k=1-k;
    cs  = pDC->GetTextExtent(strD1,strD1.GetLength());
    Pos+=cs.cx;
  }  
  pDC->SetTextColor(crOldText);
}



IMPLEMENT_DYNCREATE(CExplanStepView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CExplanStepView
CExplanStepView::CExplanStepView() { }

BEGIN_MESSAGE_MAP(CExplanStepView, CBrView)
    //{{AFX_MSG_MAP(CExplanStepView)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//------------------------------------------------------------
// Overrides of CView and CBrView
void CExplanStepView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV==NULL && lHint==0L && 
    (pHint== NULL)||(pHint->IsKindOf(RUNTIME_CLASS(CExplanStepView))))
   Invalidate(); 
}

//------------------------------------------------------------
void CExplanStepView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=EXPLANVIEW) { 
      theApp.m_nActiveFrame = EXPLANVIEW; pFrameWnd->ViewExplan();                
    }  
  }
}

//------------------------------------------------------------
int CExplanStepView::GetRowCount()   { return (GetDocument()->m_sExplanStep.GetSize());}

//------------------------------------------------------------
void CExplanStepView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{ CBrView::GetRowWidthHeight(pDC, nRowWidth, nRowHeight);
  nRowHeight +=2;
}

//------------------------------------------------------------
void CExplanStepView::OnDrawRow(CDC* pDC, int nRow, int y)
{
  COLORREF crOldText;
  int Pos,s,k=0;
  CString strD,strD1;
  CSize  cs;
  TEXTMETRIC tm;
  CScriptDoc* pDoc = GetDocument();
  if (pDoc->m_NumStep==0) return;
  pDC->GetTextMetrics(&tm);
  crOldText = pDC->SetTextColor(RGB(0,0,128));     // Синий текст
  strD = pDoc->m_sExplanStep.GetAt(nRow);
  Pos = 10;
  while (!strD.IsEmpty()) {
    s = strD.Find('^');
    if (s<0)    { pDC->TextOut(Pos, y, strD); break; }
    strD1 = strD.Left(s);
    strD = strD.Right(strD.GetLength()-s-1);
    pDC->TextOut(Pos, y, strD1);
    if (k) pDC->SetTextColor(RGB(0,0,128)); 
    else pDC->SetTextColor(RGB(128,128,128)); 
    k=1-k;
    cs  = pDC->GetTextExtent(strD1,strD1.GetLength());
    Pos+=cs.cx;
  }
  pDC->SetTextColor(crOldText);
}

//---------------------------------------------------------------------OnKeyDown
void CExplanStepView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ CScriptDoc* pDoc = GetDocument();
   if (pDoc->m_NumStep==0) return; 
  switch (nChar)  {
  case VK_HOME:  if (pDoc->m_ActStep) pDoc->m_ActStep=0;   
                 break;
  case VK_END:   if (pDoc->m_ActStep!=pDoc->m_NumStep-1) pDoc->m_ActStep=pDoc->m_NumStep-1;
                 break;
  case VK_NEXT:  if (pDoc->m_ActStep!=pDoc->m_NumStep-1) pDoc->m_ActStep++;
                 break;
  case VK_PRIOR: if (pDoc->m_ActStep) pDoc->m_ActStep--;
                break;
  case VK_UP: OnVScroll(SB_LINEUP,  0, GetScrollBarCtrl(SB_VERT)); return;
  case VK_DOWN:  OnVScroll(SB_LINEDOWN,0, GetScrollBarCtrl(SB_VERT)); return;
  default: CScrollView::OnKeyDown(nChar, nRepCnt, nFlags); return;
  }
  pDoc->GetStep(pDoc->m_nRecAtr,pDoc->m_nRecVal);
  pDoc->UpdateAllViews(NULL,NULL,this);
}
