// EditNameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "exsylor.h"
#include "EditNameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditNameDlg dialog


CEditNameDlg::CEditNameDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEditNameDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEditNameDlg)
	m_sName = _T("");
	m_Txt = _T("");
	//}}AFX_DATA_INIT
}


void CEditNameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEditNameDlg)
	DDX_Text(pDX, IDC_EDIT1, m_sName);
	DDX_Text(pDX, IDC_STATIC1, m_Txt);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEditNameDlg, CDialog)
	//{{AFX_MSG_MAP(CEditNameDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEditNameDlg message handlers

void CEditNameDlg::OnOK() 
{ int i;
  if (!UpdateData(TRUE)) return;
  if (m_sName.GetLength() <1) return;
  CDialog::OnOK();
  do {
    i = m_sName.Find(' ');
    if (i>=0) m_sName.SetAt(i,'_');
  } while (i >= 0);
}
