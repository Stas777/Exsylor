// BoolRowView.cpp : implementation of the CBrView class
// 17.05.2007
//--------------------------------------------------------------

#include "stdafx.h"

#include "brview.h"
#include <stdlib.h>
#include <limits.h> // for INT_MAX

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CBrView, CScrollView)
//--------------------------------------------------------------
// CBrView ----------------------------------------------------
//--------------------------------------------------------------
BEGIN_MESSAGE_MAP(CBrView, CScrollView)
    //{{AFX_MSG_MAP(CBrView)
    ON_WM_KEYDOWN()
    ON_WM_SIZE()
    ON_WM_RBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//--------------------------------------------------------------
// CBrView construction, initialization, and destruction ------
//--------------------------------------------------------------
CBrView::CBrView()
{  m_nPrevRowCount=0;
 lf.lfHeight = -12;        lf.lfWidth = 0;
 lf.lfEscapement = 0;      lf.lfOrientation = 0;
 lf.lfWeight = 400;        lf.lfItalic = 0;
 lf.lfUnderline = 0;       lf.lfStrikeOut = 0;
 lf.lfCharSet = DEFAULT_CHARSET; lf.lfOutPrecision = 3;
 lf.lfClipPrecision = 2;   lf.lfQuality = 1;
 lf.lfPitchAndFamily = 31; lstrcpy(lf.lfFaceName,"Courier New");
}
CBrView::~CBrView() { }

//--------------------------------------------------------------
// CBrView updating and drawing -------------------------------
//--------------------------------------------------------------
void CBrView::OnInitialUpdate()
{ 
  m_nPrevRowCount = GetRowCount(); UpdateScrollSizes(); 
}

//--------------------------------------------------------------
void CBrView::UpdateScrollSizes()
{
  CRect rectClient;
  GetClientRect(&rectClient); CClientDC dc(this); CalculateRowMetrics(&dc);
  CSize sizeTotal(m_nRowWidth,m_nRowHeight * (min(GetRowCount(), LastViewableRow())));
  CSize sizePage(m_nRowWidth/5, max(m_nRowHeight,
                 ((rectClient.bottom/m_nRowHeight)-1)*m_nRowHeight));
  CSize sizeLine(m_nRowWidth/20, m_nRowHeight);
  SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

//--------------------------------------------------------------
// Implementation ----------------------------------------------
//------------------------------------------------------------
void CBrView::GetRowWidthHeight(CDC* pDC, int& nRowWidth, int& nRowHeight)
{ TEXTMETRIC tm;
  CFont FontNew,*FontOld;
  pDC->GetTextMetrics(&tm);
  FontNew.CreateFontIndirect(&lf);
  FontOld = pDC->SelectObject((CFont*)&FontNew);
  nRowWidth = pDC->GetDeviceCaps(HORZRES); /* ROW_WIDTH; */
  nRowHeight = tm.tmHeight;//-2; // 2 lines of text
  pDC->SelectObject((CFont*)FontOld);
  FontNew.DeleteObject();
}

//--------------------------------------------------------------
int CBrView::RowToYPos(int nRow) { return (nRow * m_nRowHeight); }

//--------------------------------------------------------------
CRect CBrView::RowToWndRect(CDC* pDC, int nRow)
{ int nHorzRes = pDC->GetDeviceCaps(HORZRES);
  CRect rect(0, nRow * m_nRowHeight, nHorzRes, (nRow + 1) * m_nRowHeight);
  pDC->LPtoDP(&rect);
  return rect;
}

//--------------------------------------------------------------
int CBrView::LastViewableRow() { return (INT_MAX / m_nRowHeight - 1); }

//--------------------------------------------------------------
void CBrView::RectLPtoRowRange(const CRect& rect, int& nFirstRow,
                               int& nLastRow, BOOL bIncludePartiallyShownRows)
{
 int nRounding = bIncludePartiallyShownRows? 0 : (m_nRowHeight - 1);
 nFirstRow = (rect.top + nRounding) / m_nRowHeight;
 nLastRow = min( (rect.bottom - nRounding) / m_nRowHeight, GetRowCount() - 1);
}

//--------------------------------------------------------------
void CBrView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{ CScrollView::OnPrepareDC(pDC, pInfo);  CalculateRowMetrics(pDC); }

//--------------------------------------------------------------
void CBrView::OnDraw(CDC* pDC)
{ if (GetRowCount() == 0) return;
  int nFRow, nLRow, nRow, y, nLVRow;
  CRect rectClip;
  pDC->GetClipBox(&rectClip); // Get the invalidated region.
  RectLPtoRowRange(rectClip, nFRow, nLRow, TRUE);
  UpdateScrollSizes();
  nLVRow = LastViewableRow();
  for (nRow=nFRow, y = m_nRowHeight*nFRow; nRow <= nLRow; nRow++, y += m_nRowHeight)
    { if (nRow > nLVRow) { CString W="Too many strings!"; pDC->TextOut(0,y,W); break; }
      OnDrawRow(pDC, nRow, y);
    }
}

//--------------------------------------------------------------
// CBrView commands -------------------------------------------
//--------------------------------------------------------------
void CBrView::OnSize(UINT nType, int cx, int cy)
{  UpdateScrollSizes();  CScrollView::OnSize(nType, cx, cy); }

//--------------------------------------------------------------
void CBrView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{ switch (nChar)  {
  case VK_HOME: OnVScroll(SB_TOP,      0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_END:  OnVScroll(SB_BOTTOM,   0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_UP:   OnVScroll(SB_LINEUP,   0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_DOWN: OnVScroll(SB_LINEDOWN, 0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_PRIOR: OnVScroll(SB_PAGEUP,  0, GetScrollBarCtrl(SB_VERT)); break;
  case VK_NEXT:  OnVScroll(SB_PAGEDOWN,0, GetScrollBarCtrl(SB_VERT)); break;
  default:       CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
  }
}

void PutNumber(CDC* pDC, int i, int y, CFont* FontOld, CFont* FontNew, LOGFONT * lf)
{ char buf[12];
  wsprintf(buf,"%4d",i);
  pDC->SelectObject((CFont*)FontOld);
  FontNew->DeleteObject();
  lf->lfWeight=700;
  FontNew->CreateFontIndirect(lf);
  FontOld = pDC->SelectObject((CFont*)FontNew);
  pDC->SetTextColor(RGB(0,128,0));
  pDC->TextOut(1, y, buf,4);
  pDC->SelectObject((CFont*)FontOld);
  FontNew->DeleteObject();
  lf->lfWeight=400;
  FontNew->CreateFontIndirect(lf);
  FontOld = pDC->SelectObject((CFont*)FontNew);
}

//------------------------------------------------------------
void CBrView::OnRButtonDown(UINT nFlags, CPoint point)
{ GetParentFrame()->BringWindowToTop();  CScrollView::OnRButtonDown(nFlags, point); }
