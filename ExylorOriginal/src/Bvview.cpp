// 17.05.2007 ---------------CBVView--------------------
//------------------------------------------------------

#include "stdafx.h"
#include "Exsylor.h"
#include "scrdoc.h"
#include "mainfrm.h"
#include "brview.h"
#include "bvview.h"
#include "trbzview.h"
#include "treeview.h"

#include <stdlib.h>
#include <string.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CBVView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBVView
CBVView::CBVView() { }

BEGIN_MESSAGE_MAP(CBVView, CBrView)
    //{{AFX_MSG_MAP(CBVView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------------------------
// Overrides of CView and CBrView
void CBVView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV!=NULL && theApp.m_nActiveFrame!=DBVIEW) return;
  if ((pV==NULL && lHint==0L && pHint== NULL) ||
       (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTreeView))) ||
       (pHint!= NULL  && pHint->IsKindOf(RUNTIME_CLASS(CkAttrArray))) )
    Invalidate();
}

//------------------------------------------------------------
void CBVView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
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
int CBVView::GetRowCount() { return (1); }

//------------------------------------------------------------
void CBVView::OnDrawRow(CDC* pDC, int nRow, int y)
{ COLORREF crOldText;
  CFont FontNew,*FontOld;
  int width,i,Pos;
  TEXTMETRIC tm;
  CSize  cs;
  CkAttr* pAttr;
  CString W;

  pDC->GetTextMetrics(&tm);
  CScriptDoc* pDoc = GetDocument();

  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);

  crOldText = pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y+1;
  rectSelection.bottom = y + m_nRowHeight+1;
  pDC->FillRect(&rectSelection, (CBrush*)pDC->SelectStockObject(WHITE_BRUSH)); // Всю строку сделать белой

  if (theApp.CurrentTask&NEW_SAMPLE) i=pDoc->m_pSamples.GetSize();
  else                               i=pDoc->m_ActSmp;
  PutNumber(pDC,i,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);

  for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    pAttr = pDoc->m_pAttrObj.GetAt(i);
    W= pAttr->m_DFlag.BitChar('1',Symbol0);
    cs  = pDC->GetTextExtent(W,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, W,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  }
  pDC->SetTextColor(crOldText);
  pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CBVRegView, CBrView)

/////////////////////////////////////////////////////////////////////////////
// CBVRegView
CBVRegView::CBVRegView() { }

BEGIN_MESSAGE_MAP(CBVRegView, CBrView)
    //{{AFX_MSG_MAP(CBVRegView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------------------------
// Overrides of CBrView
void CBVRegView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV!=NULL && theApp.m_nActiveFrame!=KBVIEW) return;
  if ((pV==NULL && lHint==0L && pHint== NULL) ||
       (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTrRegView))) ||
       (pHint!= NULL  && pHint->IsKindOf(RUNTIME_CLASS(CkAttrArray))) )
    Invalidate();
}

//------------------------------------------------------------
void CBVRegView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
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
int CBVRegView::GetRowCount() { return (1); }

//------------------------------------------------------------
void CBVRegView::OnDrawRow(CDC* pDC, int nRow, int y)
{ COLORREF crOldText;
  CFont FontNew,*FontOld;
  int width,i,Pos,n,k,k1;
  char buf[128];
  TEXTMETRIC tm;
  CSize  cs;
  CkAttr* pAttr;

  pDC->GetTextMetrics(&tm);
  CScriptDoc* pDoc = GetDocument();

  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);

  crOldText = pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y+1;
  rectSelection.bottom = y + m_nRowHeight+1;
  pDC->FillRect(&rectSelection, (CBrush*)pDC->SelectStockObject(WHITE_BRUSH)); // Всю строку сделать белой

  if (theApp.CurrentTask&NEW_REGUL)   i=pDoc->m_pReguls.GetSize();
  else                                i=pDoc->m_ActReg;
  PutNumber(pDC,i,y,FontOld,&FontNew,&lf);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);

  for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    pAttr = pDoc->m_pAttrObj.GetAt(i);
    k = pAttr->m_KifFlag.CountBit();
    k1 = pAttr->m_KthenFlag.CountBit();
    for (n=0; n<(int)pDoc->m_DomVal[i]; n++) {
      if (k)  buf[n]= (pAttr->m_KifFlag.GetBitAt(n)==0) ? '1':Symbol0;
      else    buf[n]=  pAttr->m_KthenFlag.GetBitAt(n)     ? '1':Symbol0;
    }
    buf[n]='\0';
    cs  = pDC->GetTextExtent(buf,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, buf,pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  }
  pDC->SetTextColor(crOldText);
  pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}



/////////////////////////////////////////////////////////////////////////////
// CBVObView
/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CBVObView, CBrView)

/////////////////////////////////////////////////////////////////////////////

CBVObView::CBVObView() { }

BEGIN_MESSAGE_MAP(CBVObView, CBrView)
    //{{AFX_MSG_MAP(CBVObView)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


//------------------------------------------------------------
// Overrides of CView and CBrView
void CBVObView::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{ if (pV!=NULL && theApp.m_nActiveFrame!=OBVIEW) return;
  if ((pV==NULL && lHint==0L && pHint== NULL) ||
       (pV!=NULL && pV->IsKindOf(RUNTIME_CLASS(CTrObView))) ||
       (pHint!= NULL  && pHint->IsKindOf(RUNTIME_CLASS(CkAttrArray))) )
    Invalidate();
}

//------------------------------------------------------------
void CBVObView::OnActivateView( BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{ CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
  if (bActivate) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    if (theApp.m_nActiveFrame!=OBVIEW) {  //  change toolbars if it's nessesary
      if (theApp.CurrentTask&OBJECT) pFrameWnd->ViewRec();
      //else                               pFrameWnd->ViewDBEdit();
      theApp.m_nActiveFrame = OBVIEW;
    }
  }
}

//------------------------------------------------------------
int CBVObView::GetRowCount() { return (1); }

//------------------------------------------------------------
void CBVObView::OnDrawRow(CDC* pDC, int nRow, int y)
{ COLORREF crOldText;
  CFont FontNew,*FontOld;
  int width,i,Pos;
  TEXTMETRIC tm;
  CSize  cs;
  CkAttr* pAttr;
  CString W;
  pDC->GetTextMetrics(&tm);
  CScriptDoc* pDoc = GetDocument();

  width = tm.tmAveCharWidth;  //Ширина одного символа
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);

  crOldText = pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  CRect rectSelection;
  pDC->GetClipBox(&rectSelection);
  rectSelection.top = y+1;
  rectSelection.bottom = y + m_nRowHeight+1;
  pDC->FillRect(&rectSelection, (CBrush*)pDC->SelectStockObject(WHITE_BRUSH)); // Всю строку сделать белой

  Draw(pDC,4,-2,y-1);
  Pos=40;
  pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);

  for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0) pDC->SetTextColor(crOldText);      // Черный текст
    pAttr = pDoc->m_pAttrObj.GetAt(i);
    W= pAttr->m_DFlag.BitChar('1',Symbol0);
    cs  = pDC->GetTextExtent(W,pDoc->m_DomVal[i]);
    pDC->TextOut(Pos, y, W, pDoc->m_DomVal[i]);
    Pos+=cs.cx+5;
    pDC->MoveTo(Pos-3,y); pDC->LineTo(Pos-3,rectSelection.bottom);
    if ((i&1)==0) pDC->SetTextColor(RGB(128,0,0));      // Красный текст
  }
  pDC->SetTextColor(crOldText);
  pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}

