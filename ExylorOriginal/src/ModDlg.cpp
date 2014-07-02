// ModDlg.cpp : implementation file
// 17.05.2007
//---------------------------------

#include "stdafx.h"
#include "Exsylor.h"
#include "scrdoc.h"

#include "ModDlg.h"
#include "EditNameDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModDlg dialog
int FlList;

CModDlg::CModDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModDlg)
	m_ActAttr = _T("");
	m_ActVal = _T("");
	m_nAttr = 0;
	m_nVal = 0;
	//}}AFX_DATA_INIT
}


void CModDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModDlg)
	DDX_Control(pDX, IDC_COMBO2, m_cbVal);
	DDX_Control(pDX, IDC_COMBO1, m_cbAttr);
	DDX_CBString(pDX, IDC_COMBO1, m_ActAttr);
	DDX_CBString(pDX, IDC_COMBO2, m_ActVal);
	DDX_Text(pDX, IDC_EDIT1, m_nAttr);
	DDX_Text(pDX, IDC_EDIT2, m_nVal);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModDlg, CDialog)
	//{{AFX_MSG_MAP(CModDlg)
	ON_CBN_SETFOCUS(IDC_COMBO1, OnSetfocusCombo1)
	ON_CBN_SETFOCUS(IDC_COMBO2, OnSetfocusCombo2)
	ON_CBN_SELENDOK(IDC_COMBO1, OnSelendokCombo1)
	ON_BN_CLICKED(IDOK2, OnAdd)
	ON_BN_CLICKED(ID_DELETE, OnDelete)
	ON_BN_CLICKED(ID_EDIT, OnEditName)
	ON_BN_CLICKED(ID_IMPORT, OnImport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModDlg message handlers

BOOL CModDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  char buf[10];
  int i,count;
  CkAttr* pAttr;
  if (m_OpisAttr->GetSize()) {   // Not new
    for (i=0; i <m_OpisAttr->GetSize(); i++) {
      pAttr = m_OpisAttr->GetAt(i); m_cbAttr.AddString(pAttr->m_sTitle);
    }
    pAttr = m_OpisAttr->GetAt(0);
    count =m_OpisAttr->GetSize();
    wsprintf(buf,"%u",count);  SetDlgItemText( IDC_EDIT1, buf );
    count = pAttr->m_ValNames.GetSize();
    wsprintf(buf,"%u",count); SetDlgItemText( IDC_EDIT2, buf );
    m_cbVal.ResetContent( );
    for (i=0; i<count; i++)  m_cbVal.AddString( pAttr->m_ValNames.GetAt(i) ) ;
    m_cbAttr.SetCurSel(0);
    m_ActAttr = pAttr->m_sTitle;
    m_cbAttr.SetEditSel( 0,-1 );
  }
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CModDlg::OnOK() 
{ 
  char buf[100];
  int i,count;
  if (!UpdateData(TRUE)) return;
  count = m_cbAttr.GetCount();
  if (count <2) { AfxMessageBox (IDS_ERR_ATR); return; }
  for (i=0; i<m_OpisAttr->GetSize(); i++) {
    CkAttr* pAttr;
    pAttr = m_OpisAttr->GetAt(i);
    if ( pAttr->m_ValNames.GetSize() < 2) {
      CString W;
      W.LoadString(IDS_ERR_VAL);
      wsprintf(buf,(const char *)W,pAttr->m_sTitle);
      AfxMessageBox (buf); return;
    }; // TODO: Add extra validation here
  }
	CDialog::OnOK();
}

void CModDlg::OnAdd() 
{
  char buf[10];
  int i,count;
  if (!UpdateData(TRUE)) return;
  if (FlList)  {  // Combo1 - attr
    if (m_ActAttr.IsEmpty()) return;
    count = m_cbAttr.GetCount();
    if (count>0) {
      i = m_cbAttr.FindStringExact( -1, m_ActAttr);
      if (i>=0) { // Row was found in combo -
        m_cbAttr.SetCurSel(i); m_cbAttr.SetEditSel( 0,-1 ); return;
      }
    }
    m_cbAttr.SetCurSel(m_cbAttr.AddString(m_ActAttr));
    
    CkAttr* pAttr;
    pAttr= new CkAttr();
    pAttr->m_sTitle = m_ActAttr;
    m_OpisAttr->Add( pAttr );
    count =m_OpisAttr->GetSize();
    wsprintf(buf,"%u",count);
    SetDlgItemText( IDC_EDIT1, buf );
    m_cbVal.ResetContent( );SetDlgItemText( IDC_EDIT2, "0" );
    m_cbAttr.SetEditSel( 0,-1 );
  }
  else {          // Combo2 - val
    if (m_ActVal.IsEmpty()) return;
    CString sA;
    i = m_cbAttr.GetCurSel();
    if (i<0) return;
    m_cbAttr.GetLBText(i,sA);
    for (i=0; i<m_OpisAttr->GetSize(); i++) {
      CkAttr* pAttr;
      pAttr = m_OpisAttr->GetAt(i);
      if (sA == pAttr->m_sTitle) {
        count = m_cbVal.GetCount();
        if (count>0) {
          i = m_cbVal.FindStringExact( -1, m_ActVal);
          if (i>=0) { // Row was found in combo -
            m_cbVal.SetCurSel(i); m_cbVal.SetEditSel( 0,-1 ); return;
          }
        }
        m_cbVal.SetCurSel(m_cbVal.AddString(m_ActVal));
        pAttr->m_ValNames.Add(m_ActVal);
        count = pAttr->m_ValNames.GetSize();
        wsprintf(buf,"%u",count);
        SetDlgItemText( IDC_EDIT2, buf );
        m_cbVal.SetEditSel( 0,-1 );return;
      }
    }
    AfxMessageBox("???"); return;
  }
}

//-----------------------------------------------
inline void CModDlg::OnSetfocusCombo1() { FlList = TRUE; }

//-----------------------------------------------
inline void CModDlg::OnSetfocusCombo2() { FlList = FALSE; }

//-----------------------------------------------
void CModDlg::OnSelendokCombo1() 
{ 
  char buf[10];
  int i,count;
  CString sA;
  CkAttr* pAttr;

  if (!UpdateData(TRUE)) return;

  i = m_cbAttr.GetCurSel();
  if (i<0) return;
  m_cbAttr.GetLBText(i,sA);
  pAttr = m_OpisAttr->GetAt(i);
  if (sA != pAttr->m_sTitle) { AfxMessageBox("???"); return;  }
  count = pAttr->m_ValNames.GetSize();
  wsprintf(buf,"%u",count); SetDlgItemText( IDC_EDIT2, buf );
  m_cbVal.ResetContent( );
  for (i=0; i<count; i++)  m_cbVal.AddString( pAttr->m_ValNames.GetAt(i) ) ;
  m_cbVal.SetEditSel( 0,-1 );return;
}

//-----------------------------------------------
void CModDlg::OnDelete() 
{
  char buf[10];
  int i,count;
  CkAttr* pAttr;
  CString sA;
  if (!UpdateData(TRUE)) return; 

  if (FlList)  {  // Combo1 - attr
    i = m_cbAttr.GetCurSel();
    if (i<0) return;
    m_cbAttr.GetLBText(i,sA);
    pAttr = m_OpisAttr->GetAt(i);
    if (sA != pAttr->m_sTitle) { AfxMessageBox("???"); return;  }
    m_cbAttr. DeleteString( i );
    pAttr->m_ValNames.RemoveAll();
    delete pAttr;
    m_OpisAttr->RemoveAt(i);
    count =m_OpisAttr->GetSize();
    wsprintf(buf,"%u",count);
    SetDlgItemText( IDC_EDIT1, buf );
    m_cbVal.ResetContent( );
    if (count==0) return;
    pAttr = m_OpisAttr->GetAt(0);
    count = pAttr->m_ValNames.GetSize();
    wsprintf(buf,"%u",count);
    SetDlgItemText( IDC_EDIT2, buf );
    for (i=0; i<count; i++)  m_cbVal.AddString( pAttr->m_ValNames.GetAt(i) ) ;
    m_cbAttr.SetCurSel( 0 );
    m_cbAttr.GetLBText(0,m_ActAttr);
    m_cbAttr.SetEditSel( 0,-1 );
  }    
  else {          // Combo2 - val
    i = m_cbAttr.GetCurSel();
    if (i<0) return;
    m_cbAttr.GetLBText(i,sA);
    pAttr = m_OpisAttr->GetAt(i);    
    if (sA != pAttr->m_sTitle) { AfxMessageBox("???"); return;  }
    i = m_cbVal.GetCurSel();
    if (i<0) return;
    m_cbVal.GetLBText(i,sA);
    m_cbVal. DeleteString( i );
    pAttr->m_ValNames.RemoveAt(i);
    count = pAttr->m_ValNames.GetSize();
    wsprintf(buf,"%u",count);
    SetDlgItemText( IDC_EDIT2, buf );
    m_cbVal.SetEditSel( 0,-1 );
  }
  return;
}

//-----------------------------------------------
void CModDlg::OnEditName() 
{
  CString sA,sW,sD;
  int i,w,j;
  CkAttr* pAttr;
  CEditNameDlg dlg;
  
  if (!UpdateData(TRUE)) return; 
 
  if (FlList)  {  // Combo1 - attr
    i = m_cbAttr.GetCurSel();
    if (i<0) return;
    m_cbAttr.GetLBText(i,sW);
    pAttr = m_OpisAttr->GetAt(i);
    if (sW != pAttr->m_sTitle) { AfxMessageBox("???"); return;  }
    dlg.m_Txt="Attribute name";
  }
  else {          // Combo2 - val
    i = m_cbAttr.GetCurSel();
    if (i<0) return;
    m_cbAttr.GetLBText(i,sA);
    pAttr = m_OpisAttr->GetAt(i);
    if (sA != pAttr->m_sTitle) { AfxMessageBox("???"); return;  }
    w = m_cbVal.GetCurSel();
    if (w<0) return;
    m_cbVal.GetLBText(w,sW);
    sD = pAttr->m_ValNames.GetAt(w);
    if ( sD !=sW )             { AfxMessageBox("???"); return;  }
    dlg.m_Txt="Value name";
  }  
  dlg.m_sName = sW;
ed0: 
  if (dlg.DoModal()==IDCANCEL) return;
 
  if (FlList)  {  // Combo1 - attr
    if (dlg.m_sName==sW) return;
    j = m_cbAttr.FindStringExact( -1, dlg.m_sName);
    if (j>=0) { // Row was found in combo - 
      AfxMessageBox("???"); goto ed0;  
    }    
    pAttr->m_sTitle = dlg.m_sName;
    m_cbAttr. DeleteString( i );
    m_cbAttr. InsertString( i, dlg.m_sName );
  }
  else {          // Combo2 - val
    if (dlg.m_sName==sW) return;
    j = m_cbVal.FindStringExact( -1, dlg.m_sName);
    if (j>=0) { // Row was found in combo - 
      AfxMessageBox("???"); goto ed0;  
    }
    pAttr->m_ValNames.SetAt(w,dlg.m_sName);
    m_cbVal. DeleteString( w );
    m_cbVal. InsertString( w, dlg.m_sName );
  }
}

void CModDlg::OnImport() 
{
  CString W, W1;
  int i;
  CkAttr* pAttr = NULL;

 	W = "Model script (*.mod)|*.mod|All files (*.*)|*.*||";

  CString FileName;
  CFileDialog dlg(TRUE, NULL, NULL,
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );
  m_OpisAttr->RemoveAll();
  CFile f(FileName,CFile::modeRead);
    TRY
  {
  	CString sBuf;
  	DWORD len;
    len = f.GetLength();

    char b[5];
    while (len>0) {
      f.Read(b,1); len--;
      if (b[0]=='\r')
      {
        if (sBuf.IsEmpty())  break;
        if(sBuf[0]!=' ') // атрибут
        {
          if (pAttr != NULL) // Не первый из атрибутов
          {
            m_OpisAttr->Add(pAttr);
          }
          pAttr = new CkAttr;
          pAttr->m_sTitle = sBuf; // Имя
        }
        else  // Значение атрибута
        {
          sBuf.TrimLeft();
          if (pAttr == NULL) goto Err;
          pAttr->m_ValNames.Add(sBuf);
        }
        sBuf = ""; f.Read(b,1); len--;  // Пропускаем /n
      }
      else sBuf +=b[0];
    } 
  }
  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the reading file " + FileName);
  	CDialog::OnCancel();
    return;
  }
  END_CATCH
  if (pAttr != NULL) m_OpisAttr->Add(pAttr); // Запись последнего
 
  m_cbAttr.ResetContent( );
  m_cbVal.ResetContent( );
  char buf[10];
  int count;
  if (m_OpisAttr->GetSize()) {   // Not new
    for (i=0; i <m_OpisAttr->GetSize(); i++) {
      pAttr = m_OpisAttr->GetAt(i); m_cbAttr.AddString(pAttr->m_sTitle);
    }
    pAttr = m_OpisAttr->GetAt(0);
    count =m_OpisAttr->GetSize();
    wsprintf(buf,"%u",count);  SetDlgItemText( IDC_EDIT1, buf );
    count = pAttr->m_ValNames.GetSize();
    wsprintf(buf,"%u",count); SetDlgItemText( IDC_EDIT2, buf );
    m_cbVal.ResetContent( );
    for (i=0; i<count; i++)  m_cbVal.AddString( pAttr->m_ValNames.GetAt(i) ) ;
    m_cbAttr.SetCurSel(0);
    m_ActAttr = pAttr->m_sTitle;
    m_cbAttr.SetEditSel( 0,-1 );
  }
  return;

Err:
  AfxMessageBox("Invalid format of file " + FileName);
  f.Close();
	CDialog::OnCancel();
  return;
}
