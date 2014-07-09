// scrdoc.cpp : implementation of the CExsDoc class
// 17.05.2007 -------------------------------------

#include <ctype.h>
#include "ScrDoc.h"

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
// scrdocrg.cpp : implementation of the CScriptDoc class for SAMPLE service
// 17.05.2007
/////////////////////////////////////////////////////////////////////////////
// REGULARITY service:
/////////////////////////////////////////////////////////////////////////////
//#include "scrdocrg.cpp"

// ForDefReg
// FormOneReg
// EndOneReg
// AddOneReg
// WriteOneReg
// InsertOneReg
// GetOneReg
// DelCurrentReg
// ClearReg
// ReadCurrentReg
// NextPart
/////////////////////////////////////////////////////////////////////////////
// CScriptDoc

//---------------------------------------------------------------------ForDefReg
void CScriptDoc::ForDefReg()
{ int i,j,s,s1,k;
  CkAttr* pAttr;
  QString W;
 m_sRegulWord.clear(); m_sRegulWordCount=0;
 for (k=0; k<2; k++) {
  if (k)  {  W="FThen:"; }
  else       W="FIf:";
  m_sRegulWord.append(W);  m_sRegulWordCount++;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    s1 =  pAttr->m_KifFlag.CountBit(); s =  pAttr->m_KthenFlag.CountBit();
    if (s==0 && s1==0) continue; // Next attribute
    if (((k==0) && (s1==0)) || ((k==1) && s1)) continue; // Next attribute
    W="Q   "; W+=pAttr->m_sTitle;
    if (k==0 && m_sRegulWordCount>1) W.replace(2, '&');
    m_sRegulWord.append(W);
    W=" - "; m_sRegulWord.append(W);  m_sRegulWordCount++;
    if (s1 && (k==0)) { // For  IF
      if (s1==1) {    // One value
        W='V' + pAttr->m_ValNames.at(pAttr->m_KifFlag.LeftOne()); m_sRegulWord.append(W);
        continue;             // Next attribute   - ( OR )
      }
      if (s1==pAttr->m_ValNames.size()-1) {    // One NO value
        W="NNot ";   m_sRegulWord.append(W);
        W='V';
        for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
          if (pAttr->m_KifFlag.GetBitAt(j)==0) { W+=pAttr->m_ValNames.at(j); break; }
        m_sRegulWord.append(W); // Next attribute   - ( OR )
        continue;
      }
      for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
        if (pAttr->m_KifFlag.GetBitAt(j)) {
          W='V'; W+=pAttr->m_ValNames.at(j); m_sRegulWord.append (W);
          W=" or"; m_sRegulWord.append (W);
        }
      m_sRegulWord.removeLast();
    }
    else {                           // For THEN
      if (s==1) {    // One value
        W='V' + pAttr->m_ValNames.at(pAttr->m_KthenFlag.LeftOne()); m_sRegulWord.append (W);
        continue;             // Next attribute   - ( OR )
      }
      if (s==pAttr->m_ValNames.size()-1) {    // One NO value
        W="NNot ";   m_sRegulWord.append (W);
        W='V';
        for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
          if (pAttr->m_KthenFlag.GetBitAt(j)==0) { W+=pAttr->m_ValNames.at(j); break; }
        m_sRegulWord.append (W); // Next attribute   - ( OR )
        continue;
      }
      if (s==pAttr->m_ValNames.size()) {   // Any
        W="NAny "; m_sWord.append (W); continue; // Next attribute   - ( OR )
        continue;
      }
      for (j=0; j<pAttr->m_ValNames.size(); j++)   // Circle for all values
        if (pAttr->m_KthenFlag.GetBitAt(j)) {
          W='V'; W+=pAttr->m_ValNames.at(j); m_sRegulWord.append (W);
          W=" or"; m_sRegulWord.append (W);
        }
      m_sRegulWord.removeLast();
    }
  }
 }
}

//---------------------------------------------------------------------FormOneReg
void CScriptDoc::FormOneReg(CSample* pReg)
{ int i,j,k;
  BYTE x;
  CkAttr* pAttr;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    for (j=0; j<pAttr->m_ValNames.size(); j++) {  // Circle for all values
      k =pAttr->m_KifFlag.GetBitAt(j);
      if (k) x = 2;  
      else { k =pAttr->m_KthenFlag.GetBitAt(j); if (k) x = 1; else x=0; }       
      pReg->m_Values.append(x);
    }
    pAttr->m_KifFlag.Zero(); pAttr->m_KthenFlag.Zero();
  }
}

//---------------------------------------------------------------------EndOneReg
void CScriptDoc::EndOneReg()
{ ModeInput=FALSE; ForDefReg();
  ChangeSelectionToRowNo(1,m_ActKRow);
  //UpdateAllViews(NULL,NULL,&m_pAttrObj);
}
//---------------------------------------------------------------------AddOneReg
void CScriptDoc::AddOneReg()
{ CSample* pReg;  pReg = new (CSample);
  FormOneReg(pReg);  m_pReguls.Add(pReg); EndOneReg();
}

//---------------------------------------------------------------------WriteOneReg
void CScriptDoc::WriteOneReg()
{ CSample* pReg;  pReg = m_pReguls.GetAt(m_ActReg);  pReg->m_Values.clear();
  FormOneReg(pReg);  EndOneReg();
}

//---------------------------------------------------------------------InsertOneReg
void CScriptDoc::InsertOneReg()
{ CSample* pReg; pReg = new (CSample);
  FormOneReg(pReg); m_pReguls.m_sampleArr.insert(m_ActReg,pReg); EndOneReg();
}

//---------------------------------------------------------------------GetOneReg
void CScriptDoc::GetOneReg(int nR)
{ int i,j,iS=0;
  CSample *pReg;
  CkAttr* pAttr;
  pReg = m_pReguls.GetAt(nR);
  
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    pAttr->m_KifFlag.Zero(); pAttr->m_KthenFlag.Zero();
    for (j=0; j<pAttr->m_ValNames.size(); j++) {  // Circle for all values
      if (pReg->m_Values[iS]==2)      pAttr->m_KifFlag.SetBitAt(j,1); 
      else if (pReg->m_Values[iS]==1) pAttr->m_KthenFlag.SetBitAt(j,1);
      iS++;
    }
  }
  ModeInput=FALSE; ForDefReg();
}

//---------------------------------------------------------------------DelCurrentReg
void CScriptDoc::DelCurrentReg()
{ if (m_pReguls.m_sampleArr.size() > 1) {
    m_pReguls.m_sampleArr.remove(m_ActReg);
    if (m_ActReg>=m_pReguls.m_sampleArr.size()) m_ActReg--;
    ReadCurrentReg();
  }
  //else AfxMessageBox(IDS_LAST_ROW_DEL);
}

//---------------------------------------------------------------------ClearReg
void CScriptDoc::ClearReg()
{ int i;
  CkAttr* pAttr;
  for (i=0; i<m_pAttrObj.GetSize(); i++) {  // Circle for all attributes
    pAttr = m_pAttrObj.GetAt(i);
    pAttr->m_KifFlag.Zero(); pAttr->m_KthenFlag.Zero();
  }
  EndOneReg();
}


//---------------------------------------------------------------------ReadCurrentReg
void CScriptDoc::ReadCurrentReg()
{ GetOneReg(m_ActReg); ChangeSelectionToRowNo(1,m_ActKRow);
  ChangeSelectionToRegNo(m_ActReg);
  //UpdateAllViews(NULL,NULL,&m_pAttrObj);
}

//------------------------------------------------------------------NextPart
void CScriptDoc::NextPart(){
    if (ModeInput==FALSE) ModeInput = TRUE;
    else ModeInput=FALSE;
    ForDefReg();  // For wordregview
    ChangeSelectionToRowNo(1,m_ActKRow);
    //UpdateAllViews(NULL,NULL,&m_pAttrObj);
}
