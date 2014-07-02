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

/////////////////////////////////////////////////////////////////////////////
// General functions for CScriptDoc   (include scrinit.cpp in scrdoc)
// 17.05.2007 -------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// Work with document:
/////////////////////////////////////////////////////////////////////////////

//#include "scrinit.cpp"

// ChangeSelectionNextRowNo - for tree
// ChangeSelectionToRowNo - for tree
// ChangeSelectionNextSmpNo - for bmview
// ChangeSelectionToSmpNo - for bmview
// ChangeSelectionNextRegNo
// ChangeSelectionToRegNo
// NextView

// CScriptDoc() - constructor
// ~CScriptDoc() - destuctor
// DeleteContents
// OnNewDocument
// OnOpenDocument
// OnSaveDocument
// OnCloseDocument
// Serialize
// AssertValid
// Dump

/////////////////////////////////////////////////////////////////////////////
//--------------------------------------------------------------- ChangeSelectionNextRowNo
void CScriptDoc::ChangeSelectionNextRowNo(BOOL bNext,int& m_ActRow)
{ int w,j;
  if (bNext) {
    if (m_ActRow < (m_nAttributes +m_nValues)-1) ++m_ActRow;
    w = m_TreeRow.GetAt(m_ActRow); j = LOBYTE(w);
    if (j == 0xff) ++m_ActRow;
  }                                              // Next
  else  {
    if (m_ActRow>0)       --m_ActRow;
    w = m_TreeRow.GetAt(m_ActRow); j = LOBYTE(w);
    if (j == 0xff && m_ActRow>0)        --m_ActRow;
   }   // Prev
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActRow+1,0)),this);
}

//--------------------------------------------------------------- ChangeSelectionToRowNo
void CScriptDoc::ChangeSelectionToRowNo(int nNewNo, int& m_ActRow)
{ int w,j;
  w = m_TreeRow.GetAt(nNewNo); j = LOBYTE(w); if (j == 0xff) nNewNo++;
  m_ActRow = nNewNo;
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActRow+1,0)),this);
}


//--------------------------------------------------------------- ChangeSelectionNextRowNo
void CScriptDoc::ChangeSelectionNextSmpNo(BOOL bNext)
{
  if (bNext) { if (m_ActSmp < m_pSamples.GetSize()-1) ++m_ActSmp; }   // Next
  else  {      if (m_ActSmp>0)       --m_ActSmp;                   }   // Prev
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActSmp+1,0)),&m_pSamples);
}

//--------------------------------------------------------------- ChangeSelectionToRowNo
void CScriptDoc::ChangeSelectionToSmpNo(int nNewNo)
{ m_ActSmp = nNewNo;
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActSmp+1,0)),&m_pSamples); }

//--------------------------------------------------------------- ChangeSelectionNextRowNo
void CScriptDoc::ChangeSelectionNextRegNo(BOOL bNext)
{
  if (bNext) { if (m_ActReg < m_pReguls.GetSize()-1) ++m_ActReg; }   // Next
  else  {      if (m_ActReg>0)       --m_ActReg;                 }   // Prev
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActReg+1,0)),&m_pReguls);
}

//--------------------------------------------------------------- ChangeSelectionToRowNo
void CScriptDoc::ChangeSelectionToRegNo(int nNewNo)
{ m_ActReg = nNewNo;
  UpdateAllViews(NULL,(LPARAM)(MAKELONG(m_ActReg+1,0)),&m_pReguls); }

//--------------------------------------------------------------- NextView
void CScriptDoc::NextView(CRuntimeClass* pViewClass)
{ CView* pView;
  POSITION pos = GetFirstViewPosition();
  while (pos != NULL) {
    pView = GetNextView(pos);
    if (pView->IsKindOf(pViewClass)) {
      pView->GetParentFrame()->SetActiveView(pView);
      UpdateAllViews(NULL,0L,NULL);
    }
  }
}



/////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------- DeleteContents
void CScriptDoc::DeleteContents()
{ m_pAttrObj.RemoveAll();
  m_TreeRow.RemoveAll();
  m_nAttributes = 0;    // Number of attributes
  m_nValues = 0;        // Number of values generally
  m_KBMap.RemoveAll();  // Map of knowledge script blocks
  m_DBMap.RemoveAll();  // Map of data script blocks
  m_ActKB="";           // Name of active knowledge script blok
  m_ActDB="";           // Name of active data script blok
  if (m_pSamples.GetSize()) m_pSamples.RemoveAll();
  if (m_pReguls.GetSize()) m_pReguls.RemoveAll();
  m_DomAdr.RemoveAll();  m_DomVal.RemoveAll(); m_nDom = 0;
  if (!MaskDom.IsEmpty()) MaskDom.RemoveAll();
  m_sWord.RemoveAll();  //m_BVector.Empty();
  m_sRegulWord.RemoveAll();
  theApp.CurrentTask=-1;
}

//--------------------------------------------------------------- OnNewDocument
BOOL CScriptDoc::OnNewDocument()
{
  m_nAttributes = 0;    // Number of attributes
  m_nValues = 0;        // Number of values generally
  if (!CDocument::OnNewDocument()) return FALSE;
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  theApp.CurrentTask=0;
  pFrameWnd-> ViewMod();
  if (!NewModel()) return FALSE;
  UpdateAllViews(NULL,NULL,NULL);
  return TRUE;
}

//--------------------------------------------------------------- OnOpenDocument
BOOL CScriptDoc::OnOpenDocument(const char* pszPathName )
{
  m_nAttributes = 0;    // Number of attributes
  m_nValues = 0;        // Number of values generally
  if (!CDocument::OnOpenDocument(pszPathName )) return FALSE;

  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  theApp.CurrentTask=0;
  pFrameWnd-> ViewMod();
  InitModel();
  UpdateAllViews(NULL,NULL,NULL);
  return TRUE;
}

//--------------------------------------------------------------- OnSaveDocument
BOOL CScriptDoc::OnSaveDocument(const char* pszPathName)
{ if (!CDocument::OnSaveDocument(pszPathName))   return FALSE;
  theApp.UpdateIniFileWithDocPath(pszPathName);  return TRUE;
}

//--------------------------------------------------------------- OnSaveDocument
void CScriptDoc::OnCloseDocument()
{ CDocument::OnCloseDocument();
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> ViewOut();
}

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc serialization

//--------------------------------------------------------------- Serialize
void CScriptDoc::Serialize(CArchive& ar)
{ if (ar.IsStoring()) { 
    ar<<(WORD)m_nAttributes; 
    ar<<(WORD)m_nValues; 
    ar<<m_ActDB; 
    ar<<m_ActKB; 
}
  else {
    WORD N; ar>>N; m_nAttributes=N; 
    ar>>N; m_nValues=N; 
    ar>>m_ActDB; 
    ar>>m_ActKB; 
  }
  m_pAttrObj.Serialize(ar);
  m_KBMap.Serialize(ar); 
  m_DBMap.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc diagnostics

#ifdef _DEBUG
void CScriptDoc::AssertValid() const
{ CDocument::AssertValid(); }

void CScriptDoc::Dump(CDumpContext& dc) const
{ CDocument::Dump(dc); }
#endif //_DEBUG
