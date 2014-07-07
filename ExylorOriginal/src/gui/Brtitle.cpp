// 06.05.97 23:48 ---------------------------------------
// brtitle.cpp : implementation file
//
#include "stdafx.h"
#include "Exsylor.h"
#include "scrdoc.h"
#include "brtitle.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////////////
// CBrTitle
IMPLEMENT_DYNCREATE(CBrTitle, CScrollView)
CBrTitle::CBrTitle()
{
 lf.lfHeight = -12;        lf.lfWidth = 0;
 lf.lfEscapement = 0;      lf.lfOrientation = 0;
 lf.lfWeight = 400;        lf.lfItalic = 0;
 lf.lfUnderline = 0;       lf.lfStrikeOut = 0;
 lf.lfCharSet = DEFAULT_CHARSET; lf.lfOutPrecision = 3;
 lf.lfClipPrecision = 2;   lf.lfQuality = 1;
 lf.lfPitchAndFamily = 31; lstrcpy(lf.lfFaceName,"Courier New");
}
CBrTitle::~CBrTitle() { }

//-------------------------------------------------------------
void CBrTitle::OnUpdate(CView* pV, LPARAM lHint, CObject* pHint)
{
  if (pV==NULL && lHint==0L && pHint==NULL) Invalidate();
}

//-------------------------------------------------------------
BEGIN_MESSAGE_MAP(CBrTitle, CScrollView)
    //{{AFX_MSG_MAP(CBrTitle)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrTitle drawing
void CBrTitle::OnInitialUpdate() { UpdateScrollSizes();  EnableWindow(FALSE);}

//------------------------------------------------------------
void CBrTitle::CalculateRowMetrics(CDC* pDC)
{  TEXTMETRIC tm;
  CFont FontNew,*FontOld;
  pDC->GetTextMetrics(&tm);
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  m_nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
  m_nRowHeight = tm.tmHeight; // 2 lines of text
  pDC->SelectObject((CFont*)FontOld);
  FontNew.DeleteObject();
}

//--------------------------------------------------------------
void CBrTitle::UpdateScrollSizes()
{ CRect rectClient;
 GetClientRect(&rectClient); CClientDC dc(this);
 CalculateRowMetrics(&dc);
 CSize sizeTotal(m_nRowWidth, m_nRowHeight);
 CSize sizePage(m_nRowWidth/5,m_nRowHeight);
 CSize sizeLine(m_nRowWidth/20, m_nRowHeight);
 SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

//------------------------------------------------------------
void CBrTitle::OnDraw(CDC* pDC)
{ CBrush brushBackground;
 CPen penL,*penOld;
 COLORREF crOldBackground, crNewBackG = RGB(192,192,192);
 COLORREF crOldText, crNewText = RGB(128,0,0);
 COLORREF crNewPen = RGB(255,255,255);
 CFont FontNew, *FontOld;
 TEXTMETRIC tm;
 int width,i,Pos,j;
 char buf[1000];
 CScriptDoc* pDoc = GetDocument();
  CSize ccx;
 pDC->GetTextMetrics(&tm);
 width = tm.tmAveCharWidth;  //Ширина одного символа

 penL.CreatePen(PS_SOLID,1,crNewPen);
 brushBackground.CreateSolidBrush(crNewBackG);

 crOldText = pDC->SetTextColor(crNewText);
 crOldBackground = pDC->SetBkColor(crNewBackG);
 penOld = pDC->SelectObject(&penL );

 CRect rectClient;
 GetClientRect(&rectClient);  pDC->DPtoLP(&rectClient);
 (rectClient.top)++; pDC->FillRect(&rectClient, &brushBackground);

 int nSp,nSmm;
 CSize lw;
 nSp = pDC->GetDeviceCaps(HORZRES); nSmm = pDC->GetDeviceCaps(HORZSIZE);
 pDC->MoveTo(0, 3);  pDC->LineTo(rectClient.right, 3);
 pDC->MoveTo(38, 3);
 pDC->LineTo(38,rectClient.bottom);
 pDC->SelectObject((CPen*)penOld);  penL.DeleteObject();
 lw = pDC->GetTextExtent("N",1);
 pDC->TextOut((37-lw.cx)/2,6,"N",1);
 pDC->MoveTo(0, 2);  pDC->LineTo(rectClient.right, 2);
 pDC->MoveTo(37, 2);
 pDC->LineTo(37,rectClient.bottom);

 Pos=40;
 lf.lfHeight = -11;
 FontNew.CreateFontIndirect(&lf);
 FontOld = pDC->SelectObject((CFont*)&FontNew);
 width = tm.tmAveCharWidth;  //Ширина одного символа

 for (i=0; i<pDoc->m_nDom; i++) {
    if ((i&1)==0)  pDC->SetTextColor(crOldText);  // Old color text
    wsprintf(buf,"%-2u",i+1);
    if (pDoc->m_DomVal[i]==2)  pDC->TextOut(Pos, 4, buf,strlen(buf));
    else
      pDC->TextOut(Pos+(pDoc->m_DomVal[i]*width/2 -width), 4, buf,strlen(buf));
    for (j=0; j<(int) pDoc->m_DomVal[i]; j++) {
      wsprintf(buf+j,"%c",(char)((j%10)+'1'));
    }
    pDC->TextOut(Pos, 15, buf,pDoc->m_DomVal[i]);
    ccx = pDC->GetOutputTextExtent(buf,pDoc->m_DomVal[i]);
    Pos+=ccx.cx; //width;

    Pos+=5;
    pDC->MoveTo(Pos-3,3); pDC->LineTo(Pos-3,rectClient.bottom);
    if ((i&1)==0)  pDC->SetTextColor(crNewText);  // New color text
  }
 pDC->SetBkColor(crOldBackground);   pDC->SetTextColor(crOldText);
 pDC->SelectObject((CFont*)FontOld); FontNew.DeleteObject();
}
