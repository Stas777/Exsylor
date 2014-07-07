// DiaInd.cpp : implementation file
//

#include "stdafx.h"
#include "exsylor.h"
#include "DiaInd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDiaInd dialog


CDiaInd::CDiaInd(CWnd* pParent /*=NULL*/)
	: CDialog(CDiaInd::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDiaInd)
	m_chRank = FALSE;
	m_chNumber = FALSE;
	m_chProb = FALSE;
	m_Rank = 1;
	m_Number = 1;
	m_Power = 1;
	m_1 = _T("");
	m_2 = _T("");
	m_3 = _T("");
	m_4 = _T("");
	m_5 = _T("");
	m_6 = _T("");
	m_7 = _T("");
	//}}AFX_DATA_INIT
}


void CDiaInd::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDiaInd)
	DDX_Check(pDX, IDC_CHECK1, m_chRank);
	DDX_Check(pDX, IDC_CHECK2, m_chNumber);
	DDX_Check(pDX, IDC_CHECK3, m_chProb);
	DDX_Text(pDX, IDC_EDIT1, m_Rank);
	DDV_MinMaxInt(pDX, m_Rank, 1, 99);
	DDX_Text(pDX, IDC_EDIT2, m_Number);
	DDV_MinMaxInt(pDX, m_Number, 1, 1999);
	DDX_Text(pDX, IDC_EDIT3, m_Power);
	DDV_MinMaxInt(pDX, m_Power, 1, 7);
	DDX_Text(pDX, IDC_STATIC1, m_1);
	DDX_Text(pDX, IDC_STATIC2, m_2);
	DDX_Text(pDX, IDC_STATIC3, m_3);
	DDX_Text(pDX, IDC_STATIC4, m_4);
	DDX_Text(pDX, IDC_STATIC5, m_5);
	DDX_Text(pDX, IDC_STATIC6, m_6);
	DDX_Text(pDX, IDC_STATIC7, m_7);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDiaInd, CDialog)
	//{{AFX_MSG_MAP(CDiaInd)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDiaInd message handlers
