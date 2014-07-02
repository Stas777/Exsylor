// scrobj.cpp : implementation of the CCoverDoc class
// 17.05.2007 -------------------------------------
//

#include "stdafx.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "Exsylor.h"
#include "CoverDoc.h"
#include "scrdoc.h"
#include "formind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int nDoms;
CBM MaskDom;
CWordArray* DomVal;   //значность доменов
CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

extern CStringArray Ins_txt;
//void get_tx (int numb_txt,CString& Txt);
///////////////////////////////////////////////////////////////////////// Stack

IMPLEMENT_DYNCREATE(CStack, CWordArray)
CStack::CStack() { }
//---------------------------------------------------------------

BOOL CStack::Pop(WORD& El)
{ int i;
 if ((i=GetUpperBound())<0) return FALSE;
 El = CWordArray::GetAt(i);
 CWordArray::RemoveAt(i);
 return TRUE;
}

//---------------------------------------------------------------
void CStack::Push(WORD El) { CWordArray::Add(El); }


//---------------------------------------------------------------
//#include "ind.cpp"
//#include "ind_boun.cpp"


// Class realization for Script Document Objects:
/////////////////////////////////////////////////////////////////////////////
// scrobj.cpp : implementation of the CScriptDoc  Objects classes
// 06.05.97 23:51
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////// CSample

IMPLEMENT_SERIAL(CSample, CObject,1)
//------------------------------------------------------------- Constructor
CSample::CSample() { } // This empty constructor
//------------------------------------------------------------- Serialize
void CSample::Serialize(CArchive& ar) { m_Values.Serialize(ar); }
/////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////// CSampleBlock

IMPLEMENT_DYNCREATE(CSBlock, CObArray)
CSBlock::CSBlock() { }
//---------------------------------------------------------------
CSample* CSBlock::GetAt(int nIndex)  const
{ return (CSample*) CObArray::GetAt(nIndex); }
//---------------------------------------------------------------
void CSBlock::SetAt(int nIndex, CSample* newElement)
{ CObArray::SetAt(nIndex, (CObject *) newElement); }
//---------------------------------------------------------------
int CSBlock::Add(CSample* newElement)
{ return CObArray::Add((CObject *) newElement); }
//---------------------------------------------------------------
void CSBlock::RemoveAll()
{ int i;
  CSample* pSmp;
  for (i=0; i<GetSize(); i++) {
    pSmp = GetAt(i); pSmp->m_Values.RemoveAll(); delete (pSmp);
  }
  CObArray::RemoveAll();
}
//---------------------------------------------------------------
void CSBlock::Serialize(CArchive& ar)
{ if (ar.IsStoring())   // storing code here
    ar<<m_sTitle;
  else                  // loading code here
    ar>>m_sTitle; 
  CObArray::Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CBlockScriptMap

IMPLEMENT_DYNCREATE(CBlockMap, CMapStringToOb)
//--------------------------------------------------------------- Constructor
CBlockMap::CBlockMap() { }
//---------------------------------------------------------------
void CBlockMap::RemoveAll()
{ POSITION pos;
  CString key;
  CSBlock *pBlock;
  for (pos = GetStartPosition(); pos!=NULL; )  {
    GetNextAssoc(pos, key ,pBlock); 
    pBlock->m_sTitle.Empty(); pBlock->RemoveAll(); delete pBlock;
  }
  CMapStringToOb::RemoveAll();
}

//---------------------------------------------------------------
CString CBlockMap::GetFirstKey()
{ POSITION pos;
  CString key;
  CSBlock *pBlock;
  if ((pos = GetStartPosition())!=NULL)  {
    GetNextAssoc(pos, key ,pBlock);
  }
  return key;
}


void CBlockMap::Serialize(CArchive& ar)
{
  CSBlock *pBlock;
  POSITION pos;
	CString key;
	if (ar.IsStoring())
	{
    ar<<(DWORD)GetCount();
    for (pos = GetStartPosition(); pos!=NULL; )  {
      GetNextAssoc(pos, key, pBlock); 
      pBlock->Serialize(ar);
    }
  }
	else
	{
		DWORD nNewCount;
    ar>>nNewCount;
		while (nNewCount--)
		{
			pBlock = new CSBlock;
      pBlock->Serialize(ar);
      if (!pBlock->m_sTitle.IsEmpty())
			  SetAt(pBlock->m_sTitle, pBlock);
		}
	}
}



//---------------------------------------------------------------
int CBlockMap::GetElemForActive(CString& rKey)
{ CSBlock *pBS;
  if (rKey.IsEmpty()) return 0;
  if (!Lookup((const char*) rKey, pBS)) return 0;
  return pBS->GetSize();
}

//---------------------------------------------------------------
void CBlockMap::GetNextAssoc(POSITION& rNextPosition, CString& rKey,
                                CSBlock*& rValue)
{ CMapStringToOb::GetNextAssoc(rNextPosition, rKey, (CObject *&)rValue); }
//---------------------------------------------------------------
BOOL CBlockMap::Lookup(const char* key, CSBlock*& rValue)
{ return(CMapStringToOb::Lookup( key, (CObject *&)rValue)); }
//---------------------------------------------------------------
void CBlockMap::SetAt(const char* key, CSBlock* newValue)
{ CMapStringToOb::SetAt(key, (CObject *)newValue); }
/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CkAttr

IMPLEMENT_SERIAL(CkAttr, CObject,1)
//------------------------------------------------------------- Constructor
CkAttr::CkAttr() { } // This empty constructor
//------------------------------------------------------------- Serialize
void CkAttr::Serialize(CArchive& ar)
{ if (ar.IsStoring())  { ar<<m_sTitle; } // storing code here
  else                 { ar>>m_sTitle; } // loading code here
  m_ValNames.Serialize(ar);
}
/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CkAttrArray

IMPLEMENT_DYNCREATE(CkAttrArray, CObArray)
CkAttrArray::CkAttrArray() { }
//---------------------------------------------------------------
CkAttr* CkAttrArray::GetAt(int nIndex)  const
{ return (CkAttr*) CObArray::GetAt(nIndex); }
//---------------------------------------------------------------
void CkAttrArray::SetAt(int nIndex, CkAttr* newElement)
{ CObArray::SetAt(nIndex, (CObject *) newElement); }
//---------------------------------------------------------------
int CkAttrArray::Add(CkAttr* newElement)
{ return CObArray::Add((CObject *) newElement); }
//---------------------------------------------------------------
void CkAttrArray::RemoveAll()
{ int i;
  CkAttr* pAttr;
  for (i=0; i<GetSize(); i++) {
    pAttr = GetAt(i);
    pAttr->m_ValNames.RemoveAll(); pAttr->m_DFlag.Empty();
    pAttr->m_KifFlag.Empty(); pAttr->m_KthenFlag.Empty();
    delete (pAttr);
  }
  CObArray::RemoveAll();
}

/////////////////////////////////////////////////////////////////////////////


