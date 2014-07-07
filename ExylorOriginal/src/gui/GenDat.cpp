// GenDat.cpp : implementation file
//

#include "stdafx.h"
#include "exsylor.h"
#include "GenDat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenDat dialog


CGenDat::CGenDat(CWnd* pParent /*=NULL*/)
	: CDialog(CGenDat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGenDat)
	m_nRow = 0;
	m_nStart = 0;
	//}}AFX_DATA_INIT
}


void CGenDat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGenDat)
	DDX_Text(pDX, IDC_EDIT1, m_nRow);
	DDX_Text(pDX, IDC_EDIT2, m_nStart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGenDat, CDialog)
	//{{AFX_MSG_MAP(CGenDat)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenDat message handlers
