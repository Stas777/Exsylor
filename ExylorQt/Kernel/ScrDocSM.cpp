// scrdoc.cpp : implementation of the CExsDoc class
// 17.05.2007 -------------------------------------

//#include "stdafx.h"
//#include <io.h>
#include <ctype.h>
//#include <sys\types.h>
//#include <sys\stat.h>
#include "ScrDoc.h"
#include "BaseBool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern int nDoms;
extern CBM MaskDom;
extern QVector<int>* DomVal;   //значность доменов
extern QVector<int>* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

extern QVector<QString> Ins_txt;

void get_tx (int numb_txt, QString& Txt);

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
  QString W;

// For WordView
  m_sWord.clear(); m_sWordCount=0;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (s=j=0; j<pAttr->m_ValNames.size(); j++) {  // Circle for all values
      s+=pAttr->m_DFlag.GetBitAt(j);
    }
    if (s==0)   continue;    // Next attribute
    W='Q'; W+=pAttr->m_sTitle;  m_sWord.append (W);
    W=" - "; m_sWord.append (W);  m_sWordCount++;
    if (s==1) {    // One value
      W='V' + pAttr->m_ValNames.at(pAttr->m_DFlag.LeftOne()); m_sWord.append (W);
      continue;    // Next attribute   - ( OR )
    }
    if (s==pAttr->m_ValNames.size()-1) {    // One NO value
      W="NNot ";   m_sWord.append (W);  W='V';
      for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
        if (!pAttr->m_DFlag.GetBitAt(j)) { W+=pAttr->m_ValNames.at(j); break; }
      m_sWord.append(W); // Next attribute   - ( OR )
      continue;
    }
    if (s==pAttr->m_ValNames.size()) {   // Any
      W="NAny "; m_sWord.append(W); continue; // Next attribute   - ( OR )
      continue;
    }
    for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
      if (pAttr->m_DFlag.GetBitAt(j)) {
        W='V'; W+=pAttr->m_ValNames.at(j); m_sWord.append (W);
        W=" or "; m_sWord.append(W);
      }
    m_sWord.removeLast();
  }
}

//---------------------------------------------------------------------FormOneSmp
void CScriptDoc::FormOneSmp(CSample* pSmp)
{ int i,j;
  CkAttr* pAttr;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (j=0; j<pAttr->m_ValNames.size(); j++) {  // Circle for all values
      pSmp->m_Values.append(pAttr->m_DFlag.GetBitAt(j));
    }
    pAttr->m_DFlag.Zero();
  }
}

//---------------------------------------------------------------------EndOneSmp
void CScriptDoc::EndOneSmp() {
    ForDefSmp();
    ChangeSelectionToRowNo(1,m_ActDRow);
    //UpdateAllViews(NULL,NULL,&m_pAttrObj);
}

//---------------------------------------------------------------------AddOneSmp
void CScriptDoc::AddOneSmp()
{ CSample* pSmp; pSmp = new (CSample);
  FormOneSmp(pSmp);  m_pSamples.Add(pSmp); EndOneSmp();
}

//---------------------------------------------------------------------WriteOneSmp
void CScriptDoc::WriteOneSmp() {
    CSample* pSmp; pSmp = m_pSamples.GetAt(m_ActSmp); pSmp->m_Values.clear();
    FormOneSmp(pSmp); EndOneSmp();
}

//---------------------------------------------------------------------InsertOneSmp
void CScriptDoc::InsertOneSmp() {
    CSample* pSmp;  pSmp = new (CSample);
    FormOneSmp(pSmp);  m_pSamples.m_sampleArr.insert(m_ActSmp,pSmp); EndOneSmp();
}

//---------------------------------------------------------------------GetOneSmp
void CScriptDoc::GetOneSmp(int nR)
{ int i,j,iS=0;
  CSample *pSmp;
  CkAttr* pAttr;
  pSmp = m_pSamples.GetAt(nR);

  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (j=0; j<pAttr->m_ValNames.size(); j++) {  // Circle for all values
      pAttr->m_DFlag.SetBitAt(j,pSmp->m_Values[iS++]);
    }
  }
  ForDefSmp();
}

//---------------------------------------------------------------------DelCurrentSmp
void CScriptDoc::DelCurrentSmp()
{ if (m_pSamples.m_sampleArr.size() > 1) {
    m_pSamples.m_sampleArr.remove(m_ActSmp);
    if (m_ActSmp>=m_pSamples.m_sampleArr.size()) m_ActSmp--;
    ReadCurrentSmp();
  }
  //else AfxMessageBox(IDS_LAST_ROW_DEL);
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
void CScriptDoc::ReadCurrentSmp() {
    GetOneSmp(m_ActSmp); ChangeSelectionToRowNo(1,m_ActDRow);
    ChangeSelectionToSmpNo(m_ActSmp);
    //UpdateAllViews(NULL,NULL,&m_pAttrObj);
}

