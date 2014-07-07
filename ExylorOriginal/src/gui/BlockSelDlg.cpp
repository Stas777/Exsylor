// BlockSelDlg.cpp : implementation file
// 18.05.2007 --------------------------


#include "stdafx.h"
#include "exsylor.h"
#include "scrdoc.h"
#include "BlockSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BlockSelDlg dialog


BlockSelDlg::BlockSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(BlockSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(BlockSelDlg)
	m_Title = _T("");
	m_sName = _T("");
	//}}AFX_DATA_INIT
}


void BlockSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(BlockSelDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cbBlocks);
	DDX_Text(pDX, IDC_STATIC1, m_Title);
	DDX_CBString(pDX, IDC_COMBO1, m_sName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(BlockSelDlg, CDialog)
	//{{AFX_MSG_MAP(BlockSelDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// BlockSelDlg message handlers

BOOL BlockSelDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();
  POSITION pos;
  CString key;
  int i;
  CSBlock *pBlock;
 
  for (pos = m_pBMap->GetStartPosition(); pos!=NULL; )  {
    m_pBMap->GetNextAssoc(pos, key ,pBlock); 
    m_cbBlocks.AddString(key);
  }
  i = m_cbBlocks.FindString(0,m_sName); if (i<0) i=0;
  m_cbBlocks.ShowDropDown(TRUE);  
  m_cbBlocks.SetCurSel(i);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
