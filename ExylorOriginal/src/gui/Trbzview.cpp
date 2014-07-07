// TreeView.cpp : implementation of the CTreeView class
// 17.05.2007 ------------------------------------------
//------------------------------------------------------
#include "stdafx.h"
#include "brview.h"
#include "trbzview.h"

#include <stdlib.h>
#include <limits.h> // for INT_MAX
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrBzView

IMPLEMENT_DYNAMIC(CTrBzView, CBrView)

BEGIN_MESSAGE_MAP(CTrBzView, CBrView)
  //{{AFX_MSG_MAP(CTrBzView)
    ON_WM_LBUTTONUP()
    //}}AFX_MSG_MAP
  // Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrBzView construction/destruction

CTrBzView::CTrBzView()  { m_nPrevRowCount=0; }

CTrBzView::~CTrBzView() { }

/////////////////////////////////////////////////////////////////////////////
// CTrBzView drawing
void CTrBzView::OnDrawRow(CDC* pDC, int nRowNo, int y) { }
int CTrBzView::GetRowCount() { return 0; }
//--------------------------------------------------------------
void CTrBzView::OnInitialUpdate()
{ m_nPrevRowCount = GetRowCount();
  m_nPrevSelectedRow = GetActiveRow(); UpdateScrollSizes();
}

//--------------------------------------------------------------
void CTrBzView::UpdateRow(int nInvalidRow)
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
 InvalidateRect(&rectInvalid);
 int nSelectedRow = GetActiveRow();
 if (m_nPrevSelectedRow != nSelectedRow) {
   CRect rectOldSelection = RowToWndRect(&dc, m_nPrevSelectedRow);
   InvalidateRect(&rectOldSelection);
   m_nPrevSelectedRow = nSelectedRow;
 }
}

//--------------------------------------------------------------
void CTrBzView::UpdateScrollSizes()
{ CRect rectClient;    GetClientRect(&rectClient);
  CClientDC dc(this);  CalculateRowMetrics(&dc);
 CSize sizeTotal(0, m_nRowHeight * (min(GetRowCount(), LastViewableRow())));
 CSize sizePage(0, max(m_nRowHeight, ((rectClient.bottom/m_nRowHeight)-1)*m_nRowHeight));
 CSize sizeLine(0, m_nRowHeight);
 SetScrollSizes(MM_TEXT, sizeTotal, sizePage, sizeLine);
}

//--------------------------------------------------------------
void CTrBzView::OnDraw(CDC* pDC)
{ int nFirstRow, nLastRow;
  if (GetRowCount()==0) {
    CBrush brushBackground;   // save colors for drawing selected item on the screen
    COLORREF crNewBackG;
    COLORREF crOldBackground = 0;
    crNewBackG =::GetSysColor(COLOR_WINDOW);
    brushBackground.CreateSolidBrush(crNewBackG);
    crOldBackground = pDC->SetBkColor(crNewBackG);
    CRect rectSelection;
    pDC->GetClipBox(&rectSelection);
    pDC->FillRect(&rectSelection, &brushBackground);
    pDC->SetBkColor(crOldBackground);
    m_nPrevSelectedRow = 1;
    m_nPrevRowCount = 0;
    return;
  }
  CRect rectClip;
  pDC->GetClipBox(&rectClip); // Get the invalidated region.
  RectLPtoRowRange(rectClip, nFirstRow, nLastRow, TRUE);

  int nRow, y, nActiveRow = GetActiveRow();
  int nLastViewableRow = LastViewableRow();
 for (nRow=nFirstRow, y=m_nRowHeight*nFirstRow; nRow <= nLastRow; nRow++, y+=m_nRowHeight) {
   if (nRow > nLastViewableRow)  { AfxMessageBox("Too many rows"); break; }
   if (!pDC->IsPrinting()) { OnDrawRowWithSel(pDC, nRow, y, nRow == nActiveRow); }
 }
}

//---------------------------------------------------------------------------
// Implementation -----------------------------------------------------------
//---------------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CTrBzView message handlers
//---------------------------------------------------------------------------
void CTrBzView::OnLButtonUp(UINT nFlags, CPoint point)
{
 if (GetCapture() != this) return; // If this window (view) didn't capture the mouse,
                                   // then the user isn't drawing in this window.
 ReleaseCapture(); // Release the m. capture established at the beginning of the mouse drag.
 CBrView::OnLButtonUp(nFlags, point);
}

//----------------------------------------------------------------------------
