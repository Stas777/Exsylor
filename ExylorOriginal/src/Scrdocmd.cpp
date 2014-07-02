// scrdoc.cpp : implementation of the CExsDoc class
// 17.05.2007 -------------------------------------

#include "stdafx.h"
#include <io.h>
#include <ctype.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "Exsylor.h"
#include "scrdoc.h"
#include "moddlg.h"
#include "EditNameDlg.h"
#include "scriptvw.h"
#include "brview.h"
#include "trbzview.h"
#include "treeview.h"
#include "bmview.h"
#include "modview.h"
#include "wordview.h"
#include "mainfrm.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern int nDoms;
extern CBM MaskDom;
extern CWordArray* DomVal;   //значность доменов
extern CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

extern CStringArray Ins_txt;

void get_tx (int numb_txt,CString& Txt);

// scrdocmd.cpp : implementation of the CScriptDoc class for MODEL service
// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
// MODEL service:
/////////////////////////////////////////////////////////////////////////////
//#include "scrdocmd.cpp"

// InitModel
// NewModel
// InitTree
// -----------------Data Block
// WriteReadSmp
// CancelSampleInput
// DBClose
// DBSave
// DBDelete
// -----------------Knowledge Block
// WriteReadReg
// CancelRegInput
// KBClose
// KBSave
// KBDelete

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc

/////////////////////////////////////////////////////////////////////////////
// ***     ***   ****    ****     ******  ****
//  ***   ***   **  **   **  **   ******   **
//  **** ****  **    **  **   **  **       **
//  ** *** **  **    **  **   **  *****    **
//  **  *  **  **    **  **   **  **       **   **
//  **     **   **  **   **  **   ******   *******
// ****   ****   ****    ****     ******  ********
//////////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------InitModel
void CScriptDoc::InitModel()
{ CkAttr* pAttr;
  int i,j,s,j1;
  m_TreeRow.RemoveAll();  // For TreeView
  for (i=0; i<m_pAttrObj.GetSize(); i++) {
    pAttr = m_pAttrObj.GetAt(i);
    m_TreeRow.Add(i<<8 | 0xff);
    pAttr->m_DFlag.Empty(); pAttr->m_KifFlag.Empty();pAttr->m_KthenFlag.Empty();
    pAttr->m_DFlag.SetSize(pAttr->m_ValNames.GetSize());
    pAttr->m_KifFlag.SetSize(pAttr->m_ValNames.GetSize());
    pAttr->m_KthenFlag.SetSize(pAttr->m_ValNames.GetSize());
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++) {
       m_TreeRow.Add(i<<8|j);         // For TreeView
    }
  }
  m_nDom = m_nAttributes;
  m_DomAdr.RemoveAll(); m_DomVal.RemoveAll();   //значность доменов
  MaskDom.SetSize(m_nDom,m_nValues);
  j=0;
  for (i=0; i<m_nDom; i++) {
    m_DomAdr.Add(j);  pAttr = m_pAttrObj.GetAt(i);
    s = pAttr->m_ValNames.GetSize();  m_DomVal.Add(s);  j+=s;
    for (j1=0; j1<s; j1++)    //цикл по домену
      MaskDom.SetBitAt(i,j1+m_DomAdr[i],1);
  }
  m_DomAdr.Add(j);
  nDoms = m_nDom;   DomVal = &m_DomVal;   DomAdr = &m_DomAdr;
  UpdateAllViews(NULL,NULL,NULL);
}

//---------------------------------------------------------------------NewModel
int CScriptDoc::NewModel()
{ int i,j;
  CkAttr* pAttr,* pAttr0;       // One attribute
  CkAttrArray* pAttrAr;        // List of attributes
  CModDlg dlg;                 // Dialog for model script edition

  pAttrAr = new (CkAttrArray);
  dlg.m_OpisAttr = pAttrAr;

  if (dlg.DoModal()!=IDOK) { pAttrAr->RemoveAll(); delete (pAttrAr); return 0; }

  m_nAttributes = pAttrAr->GetSize(); // Number of attributes
  m_nValues = 0;
  m_pAttrObj.RemoveAll();
  for (i=0; i<m_nAttributes; i++) {
    pAttr = pAttrAr->GetAt(i);
    m_nValues +=pAttr->m_ValNames.GetSize(); // Number of values generally
    pAttr0 = new CkAttr();
    pAttr0->m_sTitle = pAttr->m_sTitle;
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++) {
      pAttr0->m_ValNames.Add(pAttr->m_ValNames.GetAt(j));
    }
    m_pAttrObj.Add(pAttr0);
  }
  pAttrAr->RemoveAll(); delete (pAttrAr);

  SetModifiedFlag();
  m_ActDB = "";
  m_ActKB = "";
  InitModel();
  return 1;
}

//---------------------------------------------------------------------InitTree
void CScriptDoc::InitTree(BOOL Act,BYTE Val)
{ CkAttr* pAttr;
  int i;
 if (Val) m_RowMask.Empty(); 
 if (Act)  m_ActKRow=1; else  m_ActDRow=1;
 for (i=0; i<m_pAttrObj.GetSize(); i++) {
   pAttr = m_pAttrObj.GetAt(i);
   if (Act) {
     pAttr->m_KifFlag.Empty();
     pAttr->m_KifFlag.SetSize(pAttr->m_ValNames.GetSize());
     pAttr->m_KthenFlag.Empty();
     pAttr->m_KthenFlag.SetSize(pAttr->m_ValNames.GetSize());
   }  
   else {
     pAttr->m_DFlag.Empty(); 
     pAttr->m_DFlag.SetSize(pAttr->m_ValNames.GetSize());
     if (Val) pAttr->m_DFlag.One();   else pAttr->m_DFlag.Zero();
   } 
 }
}


/////////////////////////////////////////////////////////////////////////////////
//   ****       ****   ********   ****
//   **  **    ** **   ** ** **  ** **
//   **   **  **  **      **    **  **
//   **   **  **  **      **    **  **
//   **   **  ******      **    ******
//   **  **   **  **      **    **  **
//   ****    **    **    ****  **    **
/////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------CancelSampleInput
void CScriptDoc::CancelSampleInput(BOOL Fl)
{
  if (m_pSamples.GetSize()) m_pSamples.RemoveAll();
    m_sWord.RemoveAll(); m_sWordCount=0; //m_BVector.Empty();
  if (theApp.CurrentTask&NEW_SAMPLE) theApp.CurrentTask&=~NEW_SAMPLE;
  else                              theApp.CurrentTask&=~EDIT_DB;
  ChangeSelectionToRowNo(1,m_ActDRow); UpdateAllViews(NULL,NULL,NULL);
  if (Fl==FALSE) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    CMDIChildWnd* pMDIActive = pFrameWnd->MDIGetActive();
    if (pMDIActive == NULL)  return;
    pMDIActive->MDIDestroy();
    pFrameWnd-> CreateOrActivateFrame(theApp.pScriptDocTemplate, RUNTIME_CLASS(CModView));
  }
}

//------------------------------------------------------------------DBClose
void CScriptDoc::DBClose(BOOL Fl)
{ int i,j;
  if(ChangeOb){
    if (Fl) j = MB_YESNO; else j = MB_YESNOCANCEL;
    i = AfxMessageBox(IDS_NOT_SAVE_SMP,j);
    if (i == IDYES) DBSave();    // Cancel sample input
    else if (i != IDNO) return;
  }
  CancelSampleInput(Fl);    // Cancel sample input
}

//------------------------------------------------------------------DBSave
BOOL CScriptDoc::DBSave()
{
  CSBlock* pDBS;
  CEditNameDlg dlgN;
  int i;

  dlgN.m_Txt="Data block name";
  if (!m_ActDB.IsEmpty()) dlgN.m_sName = m_ActDB;
dd0:
  if (dlgN.DoModal()==IDCANCEL || dlgN.m_sName.IsEmpty()) return FALSE;

  if (dlgN.m_sName != m_ActDB) {  // Input new name
    if (m_DBMap.Lookup((const char*) dlgN.m_sName, pDBS)) {
      i = AfxMessageBox(IDS_EXIST_SMP,MB_YESNO);
      if (i==IDNO) goto dd0;
      // Use old file name
      pDBS->RemoveAll();
    }
    else {
      pDBS = new CSBlock();
      pDBS ->m_sTitle = dlgN.m_sName;
      m_DBMap.SetAt( (const char*)dlgN.m_sName,pDBS);
    }
  }
  else {    // In Place
    m_DBMap.Lookup((const char*) dlgN.m_sName, pDBS);
    pDBS->RemoveAll();
  }

// Save data block there
  for (i=0; i<m_pSamples.GetSize(); i++) 
  {
    CSample *pSmp, *NewSmp;
    pSmp = m_pSamples.GetAt(i);
    NewSmp = new CSample;
    for (int j=0; j < pSmp->m_Values.GetSize(); j++)
      NewSmp->m_Values.Add(pSmp->m_Values.GetAt(j));
    pDBS->Add(NewSmp);
  }
  m_ActDB = dlgN.m_sName;
  SetModifiedFlag();
  return TRUE;
}

//------------------------------------------------------------------DBDelete
void CScriptDoc::DBDelete()
{ CString W;
  CSBlock* pBS;

 if (m_DBMap.Lookup((const char*) m_ActDB, pBS)) {
   pBS->m_sTitle.Empty();
   pBS->RemoveAll();
   delete (pBS);
   m_DBMap.RemoveKey( ( const char*) m_ActDB );
   SetModifiedFlag();
   m_ActDB="";
   if (m_DBMap.GetCount()>0) {
     POSITION poz = m_DBMap.GetStartPosition();
     m_DBMap.GetNextAssoc(poz, m_ActDB, pBS);
   }
   UpdateAllViews(NULL,NULL,NULL);
 }
}



/////////////////////////////////////////////////////////////////////////////////
//  **** ***  ****  ****   ****   ****     ****
//   **  **    ****  **   **  **   **  **   **
//   ** **     ** ** **  **    **  **  **   **
//   ****      ** ** **  **    **  **  **   **
//   ** **     ** ** **  **    **   *********
//   **  **    **  ****   **  **    **** ****
//  ****  **  ****  ****   ****      **   **
//------------------------------------------------------------------KBClose
void CScriptDoc::KBClose(BOOL Fl)
{ int i,j;
  if (ChangeReg) {
    if (Fl) j = MB_YESNO; else j = MB_YESNOCANCEL;
    i = AfxMessageBox(IDS_NOT_SAVE_REG,j);
    if (i == IDYES) KBSave();    // Cancel regularity input
    else if (i != IDNO) return;
  }
  CancelRegInput(Fl);    // Cancel regularity input
}

//------------------------------------------------------------------CancelRegInput
void CScriptDoc::CancelRegInput(BOOL Fl)
{
  if (m_pReguls.GetSize()) m_pReguls.RemoveAll();
  m_sWord.RemoveAll(); m_sWordCount=0;
  if (theApp.CurrentTask&NEW_REGUL) theApp.CurrentTask&=~NEW_REGUL;
  else                              theApp.CurrentTask&=~EDIT_KB;
  ChangeSelectionToRowNo(1,m_ActKRow); UpdateAllViews(NULL,NULL,NULL);
  if (Fl==FALSE) {
    CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
    CMDIChildWnd* pMDIActive = pFrameWnd->MDIGetActive();
    if (pMDIActive == NULL)  return;
    pMDIActive->MDIDestroy();
    pFrameWnd-> CreateOrActivateFrame(theApp.pScriptDocTemplate, RUNTIME_CLASS(CModView));
  }
}

//------------------------------------------------------------------KBSave
BOOL CScriptDoc::KBSave()
{ 
  CSBlock* pKBS;
  CEditNameDlg dlgN;
  int i;

  dlgN.m_Txt="Knowledge block name";
  if (!m_ActKB.IsEmpty()) dlgN.m_sName = m_ActKB;
dd0:
  if (dlgN.DoModal()==IDCANCEL || dlgN.m_sName.IsEmpty()) return FALSE;

  if (dlgN.m_sName != m_ActKB) {  // Input new name
    if (m_KBMap.Lookup((const char*) dlgN.m_sName, pKBS)) {
      i = AfxMessageBox(IDS_EXIST_REG,MB_YESNO);
      if (i==IDNO) goto dd0;
      // Use old file name
      pKBS->RemoveAll();
    }
    else {
      pKBS = new CSBlock();
      pKBS ->m_sTitle = dlgN.m_sName;
      m_KBMap.SetAt( (const char*)dlgN.m_sName,pKBS);
    }
  }
  else {    // In Place
    m_KBMap.Lookup((const char*) dlgN.m_sName, pKBS);
    pKBS->RemoveAll();
  }

// Save knowledge block there
  for (i=0; i<m_pReguls.GetSize(); i++) 
  {
    CSample *pReg, *NewReg;
    pReg = m_pReguls.GetAt(i);
    NewReg = new CSample;
    for (int j=0; j < pReg->m_Values.GetSize(); j++)
      NewReg->m_Values.Add(pReg->m_Values.GetAt(j));
    pKBS->Add(NewReg);
  }
  m_ActKB = dlgN.m_sName;
  SetModifiedFlag();
  return TRUE;
}

//------------------------------------------------------------------KBDelete
void CScriptDoc::KBDelete()
{ CString W;
  CSBlock* pBS;

 if (m_KBMap.Lookup((const char*) m_ActKB, pBS)) {
   pBS->m_sTitle.Empty();
   pBS->RemoveAll();
   delete (pBS);
   m_KBMap.RemoveKey( ( const char*) m_ActKB );
   SetModifiedFlag();
   m_ActKB="";
   if (m_KBMap.GetCount()>0) {
     POSITION poz = m_KBMap.GetStartPosition();
     m_KBMap.GetNextAssoc(poz, m_ActKB ,pBS);
   }
   UpdateAllViews(NULL,NULL,NULL);
 }
}

//------------------------------------------------------------------KBDelete
void CScriptDoc::SetModifiedFlag()
{ CString Path;
  Path = GetPathName( );
  if (Path.IsEmpty()==FALSE) 
    OnSaveDocument(Path); 
  else CDocument::SetModifiedFlag();
}