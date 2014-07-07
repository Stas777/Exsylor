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
#include "BlockSelDlg.h"
#include "GenDat.h"
#include "GenKnow.h"
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

CStringArray Ins_txt;

void get_tx (int numb_txt,CString& Txt);

extern CBM GenDat(int exp, int nRowD, CBM& MatrK);
extern CBM GenKnow(int exp, int nRowK, int Rang, int ver);
extern BOOL Reduction(CBM& Matr);

/////////////////////////////////////////////////////////////////////////////
// MODEL service:               #include "scrdocmd.cpp"
// SAMPLE service:              #include "scrdocsm.cpp"
// REGULARITY service:          #include "scrdocrg.cpp"
// RECOGNITION_PREPARE service: #include "linkuser.cpp"
// Work with explanation:       #include "SrcDocEx.cpp"
// Work with document:          #include "scrinit.cpp"
/////////////////////////////////////////////////////////////////////////////
// CScriptDoc

  //{{AFX_MSG_MAP(CScriptDoc)
    ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateScriptNew)
    ON_COMMAND(ID_MODEL_EDIT, OnModelEdit)
    ON_COMMAND(ID_DATA_NEW, OnDBNew)
    ON_UPDATE_COMMAND_UI(ID_DATA_NEW, OnUpdateDBNew)
    ON_COMMAND(ID_DATA_OPEN, OnDBOpen)
    ON_UPDATE_COMMAND_UI(ID_DATA_OPEN, OnUpdateDBOpen)
    ON_COMMAND(ID_DATA_SAVE, OnDBSave)
    ON_UPDATE_COMMAND_UI(ID_DATA_SAVE, OnUpdateDBSave)
    ON_COMMAND(ID_DATA_CLOSE, OnDBClose)
    ON_COMMAND(ID_DATA_EDIT, OnDBEdit)
    ON_COMMAND(ID_DATA_DELETE, OnDBDelete)
    ON_COMMAND(ID_KNOW_NEW, OnKBNew)
    ON_UPDATE_COMMAND_UI(ID_KNOW_NEW, OnUpdateKBNew)
    ON_COMMAND(ID_KNOW_OPEN, OnKBOpen)
    ON_COMMAND(ID_KNOW_SAVE, OnKBSave)
    ON_UPDATE_COMMAND_UI(ID_KNOW_SAVE, OnUpdateKBSave)
    ON_COMMAND(ID_KNOW_CLOSE, OnKBClose)
    ON_COMMAND(ID_KNOW_EDIT, OnKBEdit)
    ON_COMMAND(ID_KNOW_DELETE, OnKBDelete)
    ON_COMMAND(ID_DATA_ADD_SMP, OnDataAddSmp)
    ON_UPDATE_COMMAND_UI(ID_DATA_ADD_SMP, OnUpdateDataAddSmp)
    ON_COMMAND(ID_DATA_CLEAR_SMP, OnDataClearSmp)
    ON_COMMAND(ID_DATA_DEL_SMP, OnDataDelSmp)
    ON_COMMAND(ID_DATA_INSERT_SMP, OnDataInsertSmp)
    ON_COMMAND(ID_DATA_READ_SMP, OnDataReadSmp)
    ON_COMMAND(ID_DATA_WRITE_SMP, OnDataWriteSmp)
    ON_COMMAND(ID_DATA_IND, OnDataInd)
    ON_UPDATE_COMMAND_UI(ID_DATA_IND, OnUpdateDataInd)
    ON_COMMAND(ID_REG_ADD, OnRegAdd)
    ON_UPDATE_COMMAND_UI(ID_REG_ADD, OnUpdateRegAdd)
    ON_COMMAND(ID_REG_CLEAR, OnRegClear)
    ON_COMMAND(ID_REG_DEL, OnRegDel)
    ON_COMMAND(ID_REG_INSERT, OnRegInsert)
    ON_COMMAND(ID_REG_READ, OnRegRead)
    ON_COMMAND(ID_REG_WRITE, OnRegWrite)
    ON_COMMAND(ID_REG_NEXT, OnRegNext)
    ON_COMMAND(ID_RECOGN_FULL, OnRecognFull)
    ON_COMMAND(ID_RECOGN_ATR, OnRecognAtr)
    ON_COMMAND(ID_RECOGN_VAL, OnRecognVal)
    ON_COMMAND(ID_KNOW_REDUCT, OnKnowReduct)
    ON_UPDATE_COMMAND_UI(ID_KNOW_REDUCT, OnUpdateKnowReduct)
    ON_COMMAND(ID_RECOGN_OBJECT, OnRecognObject)
    ON_COMMAND(ID_RECOGN_PROOF, OnRecognProof)
    ON_UPDATE_COMMAND_UI(ID_RECOGN_PROOF, OnUpdateRecognProof)
    ON_UPDATE_COMMAND_UI(ID_RECOGN_ATR, OnUpdateRecogn)
    ON_COMMAND(ID_STEP_FIRST, OnStepFirst)
    ON_COMMAND(ID_STEP_LAST, OnStepLast)
    ON_COMMAND(ID_STEP_NEXT, OnStepNext)
    ON_UPDATE_COMMAND_UI(ID_STEP_LAST, OnUpdateStepNext)
    ON_COMMAND(ID_STEP_PREV, OnStepPrev)
    ON_UPDATE_COMMAND_UI(ID_STEP_FIRST, OnUpdateStepPrev)
    ON_COMMAND(ID_P_MATRIX, OnProofMatrix)
    ON_COMMAND(ID_P_FORMULA, OnProofFormula)
    ON_UPDATE_COMMAND_UI(ID_MODEL_EDIT, OnUpdateModel)
    ON_UPDATE_COMMAND_UI(ID_KNOW_EDIT, OnUpdateKBEdit)
    ON_UPDATE_COMMAND_UI(ID_KNOW_OPEN, OnUpdateKnowOpen)
    ON_COMMAND(ID_DATA_GEN, OnDataGen)
    ON_COMMAND(ID_KNOW_GEN, OnKnowGen)
	ON_COMMAND(ID_SYSTEM, OnSystem)
	ON_COMMAND(ID_MODEL_EXPORT, OnModelExport)
	ON_COMMAND(ID_DB_EXPORT, OnDbExport)
	ON_COMMAND(ID_DB_IMPORT, OnDbImport)
	ON_COMMAND(ID_KB_EXPORT, OnKbExport)
	ON_COMMAND(ID_KB_IMPORT, OnKbImport)
    ON_UPDATE_COMMAND_UI(ID_P_MATRIX, OnUpdateStepNext)
    ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateScriptNew)
    ON_UPDATE_COMMAND_UI(ID_MODEL_DEL, OnUpdateModel)
    ON_UPDATE_COMMAND_UI(ID_DATA_CLOSE, OnUpdateDBSave)
    ON_UPDATE_COMMAND_UI(ID_DATA_EDIT, OnUpdateDBOpen)
    ON_UPDATE_COMMAND_UI(ID_DATA_DELETE, OnUpdateDBOpen)
    ON_UPDATE_COMMAND_UI(ID_KNOW_CLOSE, OnUpdateKBSave)
    ON_UPDATE_COMMAND_UI(ID_KNOW_DELETE, OnUpdateKBEdit)
    ON_UPDATE_COMMAND_UI(ID_DATA_INSERT_SMP, OnUpdateDataAddSmp)
    ON_UPDATE_COMMAND_UI(ID_DATA_WRITE_SMP, OnUpdateDataAddSmp)
    ON_UPDATE_COMMAND_UI(ID_RECOGN_FULL, OnUpdateRecogn)
    ON_UPDATE_COMMAND_UI(ID_RECOGN_VAL, OnUpdateRecogn)
    ON_UPDATE_COMMAND_UI(ID_STEP_NEXT, OnUpdateStepNext)
    ON_UPDATE_COMMAND_UI(ID_STEP_PREV, OnUpdateStepPrev)
    ON_UPDATE_COMMAND_UI(ID_P_FORMULA, OnUpdateStepNext)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////////
// CScriptDoc construction/destruction
//-----------------------------------------------------
CScriptDoc::CScriptDoc() { }

//-----------------------------------------------------
CScriptDoc::~CScriptDoc() { }

//-----------------------------------------------------
void CScriptDoc::OnSystem()  { OnCloseDocument(); }

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc commands  /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ***     ***   ****    ****     ******  ****
//  ***   ***   **  **   **  **   ******   **
//  **** ****  **    **  **   **  **       **
//  ** *** **  **    **  **   **  *****    **
//  **  *  **  **    **  **   **  **       **   **
//  **     **   **  **   **  **   ******   *******
// ****   ****   ****    ****     ******  ********

//------------------------------------------------------------------OnModelEdit
void CScriptDoc::OnModelEdit()
{ int i,j;
  CkAttr* pAttr;
  CkAttr* pAttr0;
  CkAttrArray* pAttrAr;        // List of attributes
  CModDlg dlg;

  pAttrAr = new (CkAttrArray);

  for (i=0; i<m_pAttrObj.GetSize(); i++) {
    pAttr = m_pAttrObj.GetAt(i);
    pAttr0 = new CkAttr();
    pAttr0->m_sTitle = pAttr->m_sTitle;
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++) {
      pAttr0->m_ValNames.Add(pAttr->m_ValNames.GetAt(j));
    }
    pAttrAr->Add(pAttr0);
  }
  dlg.m_OpisAttr = pAttrAr;
  if (dlg.DoModal()==IDCANCEL) 
  { pAttrAr->RemoveAll(); delete (pAttrAr); return; }
  
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
  InitModel();
}

//---------------------------------------------------------------OnModelExport
void CScriptDoc::OnModelExport() { ModelExport(); }


/////////////////////////////////////////////////////////////////////////////////
//   ****       ****   ********   ****
//   **  **    ** **   ** ** **  ** **
//   **   **  **  **      **    **  **
//   **   **  **  **      **    **  **
//   **   **  ******      **    ******
//   **  **   **  **      **    **  **
//   ****    **    **    ****  **    **
//------------------------------------------------------------------OnDBNew
void CScriptDoc::OnDBNew()
{ theApp.CurrentTask |= NEW_SAMPLE;
  if (m_pSamples.GetSize())  m_pSamples.RemoveAll();
  InitTree(FALSE,0);
  ForDefSmp();
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pWordScriptTemplate, RUNTIME_CLASS(CTreeView));
  ChangeSelectionToRowNo(1,m_ActDRow);
  UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnDBOpen
void CScriptDoc::OnDBOpen()
{ int Res;
  BlockSelDlg dlg;
  dlg.m_sName=m_ActDB;
  dlg.m_Title.LoadString(IDS_SMP_SEL);
  dlg.m_pBMap = &m_DBMap;
  Res =dlg.DoModal();
  if (Res ==IDCANCEL) return;
  m_ActDB=dlg.m_sName;
  UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnDBSave
void CScriptDoc::OnDBSave() { if (DBSave()) CancelSampleInput(FALSE); }

//------------------------------------------------------------------OnDBClose
void CScriptDoc::OnDBClose() { DBClose(FALSE); }

//------------------------------------------------------------------OnDbExport
void CScriptDoc::OnDbExport() { DbExport(); }

//------------------------------------------------------------------OnDbImport
void CScriptDoc::OnDbImport() { DbImport();}

//------------------------------------------------------------------OnDBEdit
void CScriptDoc::OnDBEdit()
{ 
  CSBlock* pBS;
  int i;

  if (!m_DBMap.Lookup((const char*) m_ActDB, pBS)) return;
  // Проверка что какой-то блок есть

  if (m_pSamples.GetSize()) m_pSamples.RemoveAll();

  for (i = 0; i<pBS->GetSize(); i++)  
  {
    CSample *pS, *NewSmp;
    pS = pBS->GetAt(i);
    NewSmp = new CSample;
    for (int j=0; j < pS->m_Values.GetSize(); j++)
      NewSmp->m_Values.Add(pS->m_Values.GetAt(j));
    m_pSamples.Add(NewSmp);
  }
  InitTree(FALSE,0);
  theApp.CurrentTask |= EDIT_DB;
  ChangeOb = FALSE;
  m_ActSmp = 0;  GetOneSmp(m_ActSmp);
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pWordEditTemplate, RUNTIME_CLASS(CTreeView));
  ChangeSelectionToRowNo(1,m_ActDRow); // for TreeView
  UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnDBDelete
void CScriptDoc::OnDBDelete()
{ CString W; char buf[200];
  W.LoadString(IDS_DELETE_SMP); wsprintf(buf,(const char *)W,m_ActDB);
  if (AfxMessageBox(buf,MB_YESNO) == IDYES) DBDelete();
}

//------------------------------------------------------------------OnDataInd
void CScriptDoc::OnDataInd()  
{ CBM MatrCon;
 CBM MatrDis;
 if (ToMatrCon(MatrCon)==FALSE) return;
 if (Induct(MatrCon,MatrDis)) {
   m_Matr = MatrDis.Extract(0,0,MatrDis.GetCountR(),MatrDis.GetCountC());
   CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
   pFrameWnd-> CreateOrActivateFrame(theApp.pViewBMTemplate, RUNTIME_CLASS(CBM_View));
   UpdateAllViews(NULL,NULL,NULL);
 }
 else AfxMessageBox(IDS_NOT_REGUL_FOR_IND);
 return;
}

//---------------------------------------------------------OnDataGen
void CScriptDoc::OnDataGen()
{ CBM Matr;
  CBM MatrKnow;
  if (!ToMatr(MatrKnow)) return;
  CGenDat dlg;
  InitTree(FALSE,0);
  if (dlg.DoModal()==IDCANCEL) return;
  
  Matr = GenDat(dlg.m_nStart,dlg.m_nRow,MatrKnow);
  m_Matr = Matr.Extract(0,0,Matr.GetCountR(),Matr.GetCountC());
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  theApp.CurrentTask |= GEN_DB;
  pFrameWnd-> CreateOrActivateFrame(theApp.pViewBMTemplate, RUNTIME_CLASS(CBM_View));
  UpdateAllViews(NULL,NULL,NULL);
  return;
}

/////////////////////////////////////////////////////////////////////////////////
//  **** ***  ****  ****   ****   ****     ****
//   **  **    ****  **   **  **   **  **   **
//   ** **     ** ** **  **    **  **  **   **
//   ****      ** ** **  **    **  **  **   **
//   ** **     ** ** **  **    **   *********
//   **  **    **  ****   **  **    **** ****
//  ****  **  ****  ****   ****      **   **
//------------------------------------------------------------------OnKBNew
void CScriptDoc::OnKBNew()
{ theApp.CurrentTask |= NEW_REGUL;
  if (m_pReguls.GetSize())  m_pReguls.RemoveAll();
  ModeInput=FALSE;
  InitTree(TRUE,0);
  ForDefReg();
  ChangeReg = FALSE;
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pRegulTemplate, RUNTIME_CLASS(CTrRegView));
}

//------------------------------------------------------------------OnKBOpen
void CScriptDoc::OnKBOpen()
{ int Res;
  BlockSelDlg dlg;
  dlg.m_sName=m_ActKB;
  dlg.m_Title.LoadString(IDS_REG_SEL);
  dlg.m_pBMap = &m_KBMap;
  Res =dlg.DoModal();
  if (Res ==IDCANCEL) return;
  m_ActKB=dlg.m_sName;

  UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnKBSave
void CScriptDoc::OnKBSave() {if (KBSave()) CancelRegInput(FALSE); }

//------------------------------------------------------------------OnKBClose
void CScriptDoc::OnKBClose() { KBClose(FALSE); }

//------------------------------------------------------------------OnKBExport
void CScriptDoc::OnKbExport() { KbExport(); }

//------------------------------------------------------------------OnKBImport
void CScriptDoc::OnKbImport() { KbImport(); }

//------------------------------------------------------------------OnKBEdit
void CScriptDoc::OnKBEdit()
{ CSBlock* pBS;
  int i;

  if (!m_KBMap.Lookup((const char*) m_ActKB, pBS)) return;

  if (m_pReguls.GetSize()) m_pReguls.RemoveAll();

  for (i = 0; i<pBS->GetSize(); i++)  
  {
    CSample *pS, *NewReg;
    pS = pBS->GetAt(i);
    NewReg = new CSample;
    for (int j=0; j < pS->m_Values.GetSize(); j++)
      NewReg->m_Values.Add(pS->m_Values.GetAt(j));
    m_pReguls.Add(NewReg);
  }
  InitTree(TRUE,0);
  theApp.CurrentTask |= EDIT_KB;
  ChangeReg = FALSE;
  m_ActReg = 0;  GetOneReg(m_ActReg);
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pRegulEditTemplate, RUNTIME_CLASS(CTrRegView));
  ChangeSelectionToRowNo(1,m_ActKRow); // for TrRegView
  UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnKBDelete
void CScriptDoc::OnKBDelete()
{ CString W; char buf[200];
  W.LoadString(IDS_DELETE_REG ); wsprintf(buf,(const char *)W,m_ActKB);
  if (AfxMessageBox(buf,MB_YESNO) == IDYES) KBDelete();
}

//---------------------------------------------------------OnKnowGen
void CScriptDoc::OnKnowGen()
{ CBM Matr;
  CGenKnow dlg;
  InitTree(TRUE,0);
  if (dlg.DoModal()==IDCANCEL) return;
  Matr = GenKnow(dlg.m_nStart,dlg.m_nRow,dlg.m_nRank,dlg.m_nDensityProc);
  m_Matr = Matr.Extract(0,0,Matr.GetCountR(),Matr.GetCountC());
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pViewBMTemplate, RUNTIME_CLASS(CBM_View));
  UpdateAllViews(NULL,NULL,NULL);
  return;
}

//------------------------------------------------------------------OnKnowReduct
void CScriptDoc::OnKnowReduct()
{ CBM Matr;
  int n;
  if (!ToMatr(Matr)) return;
  n=Reduction(Matr);
  if (n==0) { AfxMessageBox(IDS_REDUCT_NOT); return; }
  m_Matr = Matr.Extract(0,0,Matr.GetCountR(),Matr.GetCountC());
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pViewBMTemplate, RUNTIME_CLASS(CBM_View));
  UpdateAllViews(NULL,NULL,NULL);
  return;
}



/////////////////////////////////////////////////////////////////////////////////
//   *****     ****  ***     *** ******   ****     *******
//  **   **   ** **   ***   ***   **  **   **       **  **
//  **       **  **   **** ****   **   **  **       **
//   *****   **  **   ** *** **   **  **   **       *****
//       **  ******   **  *  **   *****    **       **
//  **   **  **  **   **     **   **       **   **  **  **
//   *****  ***  *** ****   **** ****     ******** *******
//------------------------------------------------------------------OnDataReadSmp
void CScriptDoc::OnDataReadSmp()   { ReadCurrentSmp(); }
//------------------------------------------------------------------OnDataWriteSmp
void CScriptDoc::OnDataWriteSmp()  { ChangeOb = TRUE; WriteOneSmp(); }
//------------------------------------------------------------------OnDataInsertSmp
void CScriptDoc::OnDataInsertSmp() { ChangeOb = TRUE;  InsertOneSmp(); }
//------------------------------------------------------------------OnDataDelSmp
void CScriptDoc::OnDataDelSmp()    { ChangeOb = TRUE;  DelCurrentSmp(); }
//------------------------------------------------------------------OnDataAddSmp
void CScriptDoc::OnDataAddSmp()    { ChangeOb = TRUE;  AddOneSmp(); }
//------------------------------------------------------------------OnDataClearSmp
void CScriptDoc::OnDataClearSmp()  { ClearSmp(); }



/////////////////////////////////////////////////////////////////////////////////
// ******   *****   ****  ***  *** ****     *****  ******   **** ****** ***  ***
//  **  **  ** **  **  **  **  **   **     **  **   **  **   **  * ** *  **  **
//  **  **  **    **       **  **   **     **  **   **  **   **    **    **  **
//  *****   ****  **       **  **   **     **  **   *****    **    **     ** **
//  ** **   **    ** ****  **  **   **     ******   ** **    **    **       ***
//  **  **  ** **  ** **   **  **   ** **  **  **   **  **   **    **    ** **
// ***  *** *****   ***     ****   ****** ***  *** ***  *** ****  ****    ***
/////////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------OnRegAdd
void CScriptDoc::OnRegAdd()    { ChangeReg = TRUE; AddOneReg(); }
//------------------------------------------------------------------OnRegClear
void CScriptDoc::OnRegClear()  { ClearReg(); }
//------------------------------------------------------------------OnRegDel
void CScriptDoc::OnRegDel()    { ChangeReg = TRUE; DelCurrentReg(); }
//------------------------------------------------------------------OnRegInsert
void CScriptDoc::OnRegInsert() { ChangeReg = TRUE; InsertOneReg(); }
//------------------------------------------------------------------OnRegRead
void CScriptDoc::OnRegRead()   { ReadCurrentReg(); }
//------------------------------------------------------------------OnRegWrite
void CScriptDoc::OnRegWrite()  { ChangeReg = TRUE; WriteOneReg(); }
//------------------------------------------------------------------OnRegNext
void CScriptDoc::OnRegNext()   { NextPart(); }




//////////////////////////////////////////////////////////////////////////////
// ******   *****   ***   ****    **** ***  **** **** ******** *******
//  **  **  ** **  ** ** **  **  **  ** ***  **   **  **   **   **  **
//  **  **  **    **     **  ** **      ** * **   **      **    **
//  *****   ****  **     **  ** **      ** * **   **     **     ****
//  ** **   **    **     **  ** **  *** ** * **   **    **      **
//  **  **  ** **  ** ** **  **  ** **  **  ***   **   **   **  **  **
// ***  *** *****   ***   ****    ***  ****  *** **** ******** *******
//////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------OnRecognObject
void CScriptDoc::OnRecognObject()
{ if (CheckObject) FromVect(m_Vect);
  else    InitTree(FALSE,1);
  CheckObject=FALSE; theApp.CurrentTask &=~ AIM; theApp.CurrentTask|=OBJECT;
  m_sStage.LoadString(IDS_TASK_DESC);
  ForDefSmp(); UpdateAllViews(NULL,NULL,NULL);
}

//------------------------------------------------------------------OnRecognFull
void CScriptDoc::OnRecognFull()
{ theApp.CurrentTask &=~ AIM; theApp.CurrentTask |= AIM_FULL; PrepareRec(-1,-1); }

//------------------------------------------------------------------OnRecognAtr
void CScriptDoc::OnRecognAtr()
{int w;
 w = m_TreeRow.GetAt(m_ActDRow);
 theApp.CurrentTask &=~AIM; theApp.CurrentTask |=AIM_ATR;
 PrepareRec(HIBYTE(w),-1);
}

//------------------------------------------------------------------OnRecognVal
void CScriptDoc::OnRecognVal()
{ int w,j,k;
 CkAttr* pAttr;
 w = m_TreeRow.GetAt(m_ActDRow);
 j = LOBYTE(w); k = HIBYTE(w);
 pAttr = m_pAttrObj.GetAt(k);
 if (pAttr->m_DFlag.GetBitAt(j)==0) return;
 theApp.CurrentTask &=~AIM; theApp.CurrentTask |=AIM_VAL;
 PrepareRec(k,j);
}


//////////////////////////////////////////////////////////////////////////////
// ******  ******    ****    ****  *******
//  **  **  **  **  **  **  **  **  **  **
//  **  **  **  **  **  **  **  **  **
//  *****   ****    **  **  **  **  **** 
//  **      **  *   **  **  **  **  **
//  **      **  **  **  **  **  **  **
// ****    ***  ***  ****    ****  ****
//////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------OnRecognProof
void CScriptDoc::OnRecognProof(){ GetAim_ViewProof(); }

//---------------------------------------------------------OnStepFirst
void CScriptDoc::OnStepFirst()
{ m_ActStep=0; GetStep(m_nRecAtr,m_nRecVal);UpdateAllViews(NULL,NULL,NULL); }

//---------------------------------------------------------OnStepLast
void CScriptDoc::OnStepLast()
{ m_ActStep=m_NumStep-1; GetStep(m_nRecAtr,m_nRecVal);UpdateAllViews(NULL,NULL,NULL); }

//---------------------------------------------------------OnStepNext
void CScriptDoc::OnStepNext()
{ m_ActStep++; GetStep(m_nRecAtr,m_nRecVal);UpdateAllViews(NULL,NULL,NULL); }

//---------------------------------------------------------OnStepPrev
void CScriptDoc::OnStepPrev()
{ m_ActStep--; GetStep(m_nRecAtr,m_nRecVal);UpdateAllViews(NULL,NULL,NULL); }

//---------------------------------------------------------OnProofMatrix
void CScriptDoc::OnProofMatrix() { PutMatrixProof(); }

//---------------------------------------------------------OnProofFormula
void CScriptDoc::OnProofFormula() { PutFormulaProof(); }





/////////////////////////////// U P D A T E -------------------------------------

//----------------------------------------------------- ON_UPDATE
void CScriptDoc::OnUpdateScriptNew(CCmdUI* pCmdUI)        // New SCR, Open Scr
{ pCmdUI->Enable(theApp.CurrentTask < 0); }

void CScriptDoc::OnUpdateModel(CCmdUI* pCmdUI)               // EDIT
{  pCmdUI->Enable(theApp.CurrentTask == 0 &&
                  m_DBMap.GetCount() == 0 && m_KBMap.GetCount() == 0);  
}

/////////////////////////////////////////////////////////////////////////////////
void CScriptDoc::OnUpdateDBNew(CCmdUI* pCmdUI)                // NEW
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_SAMPLE|EDIT_DB|AIM))==0); }

void CScriptDoc::OnUpdateDBOpen(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_SAMPLE|EDIT_DB|AIM))==0 &&
                  m_DBMap.GetCount()>0 && !m_ActDB.IsEmpty()); }

void CScriptDoc::OnUpdateDBSave(CCmdUI* pCmdUI)               // SAVE,CLOSE
    { pCmdUI->Enable(theApp.m_nActiveFrame==DBVIEW && (
                     (theApp.CurrentTask & NEW_SAMPLE) ||
                     (theApp.CurrentTask & EDIT_DB))); }

void CScriptDoc::OnUpdateDataInd(CCmdUI* pCmdUI)
{  pCmdUI->Enable(theApp.CurrentTask == 0 &&    //Общий режим
   m_DBMap.GetCount()>0 && !m_ActDB.IsEmpty()); //Есть активный блок данных
}
/////////////////////////////////////////////////////////////////////////////////
void CScriptDoc::OnUpdateKBNew(CCmdUI* pCmdUI)                // NEW
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_REGUL|EDIT_KB))==0); }

void CScriptDoc::OnUpdateKBEdit(CCmdUI* pCmdUI)               // EDIT,DELETE
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_REGUL|EDIT_KB))==0 &&
                 m_KBMap.GetCount()>0); }  //Есть блоки знаний

void CScriptDoc::OnUpdateKnowOpen(CCmdUI* pCmdUI)             // OPEN
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_REGUL|EDIT_KB|AIM))==0 &&
                 m_KBMap.GetCount()>0); }  //Есть блоки знаний

void CScriptDoc::OnUpdateKBSave(CCmdUI* pCmdUI)               // SAVE,CLOSE
    { pCmdUI->Enable(theApp.m_nActiveFrame==KBVIEW && (
                     (theApp.CurrentTask & NEW_REGUL) ||
                     (theApp.CurrentTask & EDIT_KB))); }

void CScriptDoc::OnUpdateKnowReduct(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&(NEW_REGUL|EDIT_KB))==0 &&
                 m_KBMap.GetCount()>0);  //Есть блоки знаний
}

/////////////////////////////////////////////////////////////////////////////////
void CScriptDoc::OnUpdateDataAddSmp(CCmdUI* pCmdUI)                // ADD,WRITE,INSERT
    {   pCmdUI->Enable((theApp.CurrentTask&NEW_SAMPLE) || 
                       (theApp.CurrentTask&EDIT_DB)); }

void CScriptDoc::OnUpdateRegAdd(CCmdUI* pCmdUI)                     // ADD,WRITE,INSERT
{ pCmdUI->Enable((theApp.CurrentTask&NEW_REGUL) || 
                 (theApp.CurrentTask&EDIT_KB)); }

/////////////////////////////////////////////////////////////////////////////////
void CScriptDoc::OnUpdateRecognProof(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&AIM) && 
                 CheckObject && m_RowMask.IsEmpty()); }

void CScriptDoc::OnUpdateRecogn(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&AIM) && !CheckObject); }

void CScriptDoc::OnUpdateStepNext(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&EXPLAN) && m_NumStep  &&  
                 m_ActStep!=m_NumStep-1); }

void CScriptDoc::OnUpdateStepPrev(CCmdUI* pCmdUI)
{ pCmdUI->Enable((theApp.CurrentTask&EXPLAN) && m_NumStep && m_ActStep); }


