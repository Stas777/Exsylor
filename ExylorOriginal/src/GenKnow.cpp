// GenKnow.cpp : implementation file
//

#include "stdafx.h"
#include "exsylor.h"
#include "GenKnow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenKnow dialog


CGenKnow::CGenKnow(CWnd* pParent /*=NULL*/)
	: CDialog(CGenKnow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenKnow)
	m_nRow = 1;
	m_nStart = 1;
	m_nRank = 1;
	m_nDensityProc = 1;
	//}}AFX_DATA_INIT
}


void CGenKnow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenKnow)
	DDX_Text(pDX, IDC_EDIT1, m_nRow);
	DDX_Text(pDX, IDC_EDIT2, m_nStart);
	DDX_Text(pDX, IDC_EDIT3, m_nRank);
	DDX_Text(pDX, IDC_EDIT4, m_nDensityProc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenKnow, CDialog)
	//{{AFX_MSG_MAP(CGenKnow)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenKnow message handlers
