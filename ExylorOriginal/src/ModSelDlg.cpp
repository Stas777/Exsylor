// ModSelDlg.cpp : implementation file
// 18.05.2007 ------------------------

#include "stdafx.h"
#include "exsylor.h"
#include "scrdoc.h"
#include "ModSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CModSelDlg dialog


CModSelDlg::CModSelDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CModSelDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CModSelDlg)
    m_sName = "";
    m_Title = "";
    //}}AFX_DATA_INIT
}

void CModSelDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CModSelDlg)
    DDX_Control(pDX, IDC_COMBO1, m_cbModels);
    DDX_CBString(pDX, IDC_COMBO1, m_sName);
    DDX_Text(pDX, IDC_STATIC1, m_Title);
    //}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CModSelDlg, CDialog)
    //{{AFX_MSG_MAP(CModSelDlg)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CModSelDlg message handlers

BOOL CModSelDlg::OnInitDialog()
{  CDialog::OnInitDialog();
 POSITION pos;
 CString key;
 int i;
 CModelScript *pMod;
 
 for (pos = m_pMSMap->GetStartPosition(); pos!=NULL; )  {
   m_pMSMap->GetNextAssoc(pos, key ,pMod); 
   m_cbModels.AddString(key);
 }
 i = m_cbModels.FindString(0,m_sName); if (i<0) i=0;
 m_cbModels.ShowDropDown(TRUE);  
 m_cbModels.SetCurSel(i);
 return TRUE;  // return TRUE  unless you set the focus to a control
}

