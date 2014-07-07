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

extern CStringArray Ins_txt;

void get_tx (int numb_txt,CString& Txt);

/////////////////////////////////////////////////////////////////////////////
// scrdocsm.cpp : implementation of the CScriptDoc class for SAMPLE service
// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
// SAMPLE service:
/////////////////////////////////////////////////////////////////////////////
//#include "scrdocsm.cpp"

// ForDefSmp
// FormOneSmp
// EndOneSmp
// AddOneSmp
// WriteOneSmp
// InsertOneSmp
// GetOneSmp
// DelCurrentSmp
// ClearSmp
// ReadCurrentSmp

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc

//////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------ForDefSmp
void CScriptDoc::ForDefSmp()
{ int i,j,s;
  CkAttr* pAttr;
  CString W;

// For WordView
  m_sWord.RemoveAll(); m_sWordCount=0;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (s=j=0; j<pAttr->m_ValNames.GetSize(); j++) {  // Circle for all values
      s+=pAttr->m_DFlag.GetBitAt(j);
    }
    if (s==0)   continue;    // Next attribute
    W='Q'; W+=pAttr->m_sTitle;  m_sWord.Add (W);
    W=" - "; m_sWord.Add (W);  m_sWordCount++;
    if (s==1) {    // One value
      W='V' + pAttr->m_ValNames.GetAt(pAttr->m_DFlag.LeftOne()); m_sWord.Add (W); 
      continue;    // Next attribute   - ( OR )
    }
    if (s==pAttr->m_ValNames.GetSize()-1) {    // One NO value
      W="NNot ";   m_sWord.Add (W);  W='V';
      for (j=0; j<pAttr->m_ValNames.GetSize(); j++)   // Circle for all values
        if (!pAttr->m_DFlag.GetBitAt(j)) { W+=pAttr->m_ValNames.GetAt(j); break; }
      m_sWord.Add (W); // Next attribute   - ( OR )
      continue;
    }
    if (s==pAttr->m_ValNames.GetSize()) {   // Any
      W="NAny "; m_sWord.Add (W); continue; // Next attribute   - ( OR )
      continue;
    }
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++)   // Circle for all values
      if (pAttr->m_DFlag.GetBitAt(j)) {
        W='V'; W+=pAttr->m_ValNames.GetAt(j); m_sWord.Add (W);
        W=" or "; m_sWord.Add (W);
      }
    m_sWord.RemoveAt(m_sWord.GetUpperBound());
  }
}

//---------------------------------------------------------------------FormOneSmp
void CScriptDoc::FormOneSmp(CSample* pSmp)
{ int i,j;
  CkAttr* pAttr;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++) {  // Circle for all values
      pSmp->m_Values.Add(pAttr->m_DFlag.GetBitAt(j));
    }
    pAttr->m_DFlag.Zero();
  }
}

//---------------------------------------------------------------------EndOneSmp
void CScriptDoc::EndOneSmp()
{ ForDefSmp(); ChangeSelectionToRowNo(1,m_ActDRow); UpdateAllViews(NULL,NULL,&m_pAttrObj); }

//---------------------------------------------------------------------AddOneSmp
void CScriptDoc::AddOneSmp()
{ CSample* pSmp; pSmp = new (CSample);
  FormOneSmp(pSmp);  m_pSamples.Add(pSmp); EndOneSmp();
}

//---------------------------------------------------------------------WriteOneSmp
void CScriptDoc::WriteOneSmp()
{ CSample* pSmp; pSmp = m_pSamples.GetAt(m_ActSmp); pSmp->m_Values.RemoveAll();
  FormOneSmp(pSmp); EndOneSmp();
}

//---------------------------------------------------------------------InsertOneSmp
void CScriptDoc::InsertOneSmp()
{ CSample* pSmp;  pSmp = new (CSample);
  FormOneSmp(pSmp);  m_pSamples.InsertAt(m_ActSmp,pSmp); EndOneSmp();
}

//---------------------------------------------------------------------GetOneSmp
void CScriptDoc::GetOneSmp(int nR)
{ int i,j,iS=0;
  CSample *pSmp;
  CkAttr* pAttr;
  pSmp = m_pSamples.GetAt(nR);

  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (j=0; j<pAttr->m_ValNames.GetSize(); j++) {  // Circle for all values
      pAttr->m_DFlag.SetBitAt(j,pSmp->m_Values[iS++]);
    }
  }
  ForDefSmp();
}

//---------------------------------------------------------------------DelCurrentSmp
void CScriptDoc::DelCurrentSmp()
{ if (m_pSamples.GetSize() > 1) {
    m_pSamples.RemoveAt(m_ActSmp);
    if (m_ActSmp>=m_pSamples.GetSize()) m_ActSmp--;
    ReadCurrentSmp();
  }
  else AfxMessageBox(IDS_LAST_ROW_DEL);
}
//---------------------------------------------------------------------ClearSmp
void CScriptDoc::ClearSmp()
{ int i;
  CkAttr* pAttr;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i); pAttr->m_DFlag.Zero();
  }
  EndOneSmp();
}

//---------------------------------------------------------------------ReadCurrentSmp
void CScriptDoc::ReadCurrentSmp()
{ GetOneSmp(m_ActSmp); ChangeSelectionToRowNo(1,m_ActDRow);
  ChangeSelectionToSmpNo(m_ActSmp); UpdateAllViews(NULL,NULL,&m_pAttrObj); }

