// scrdoc.cpp : implementation of the CExsDoc class
// 17.05.2007 -------------------------------------

#include <ctype.h>
#include "ScrDoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#ifdef __MYLOCK

extern int nDoms;
extern CBM MaskDom;
extern CWordArray* DomVal;   //значность доменов
extern CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

extern CStringArray Ins_txt;

extern void get_tx (int numb_txt,CString& Txt);
extern int Proof(CBM& Matr,CBV& VectRec,CWordArray& StepProof);
extern int Recogn(CBM& Matr,CBM& RecMatr,CBV& RecVect,
                  CBV& RecRez,int nd, int nv);
/////////////////////////////////////////////////////////////////////////////
//-17.05.2007 --------------------------------include for scrdoc.cpp---------
/////////////////////////////////////////////////////////////////////////////
// RECOGNITION_PREPARE service:
/////////////////////////////////////////////////////////////////////////////
//#include "linkuser.cpp"

// RecognObject
// ToMatr
// FromMatr
/////////////////////////////////////////////////////////////////////////////
// Realize interface for user recognition programs
//----------------------------------------------------------------------


//------------------------------------------------------------------RecognObject()
void CScriptDoc::RecognObject()
{ 
  CSBlock* pBS;
  int i;

  if (!m_KBMap.Lookup((const char*) m_ActKB, pBS)) return;

  if (m_pReguls.GetSize())  m_pReguls.RemoveAll();
  for (i = 0; i<pBS->GetSize(); i++)  
  {
    CSample *pS, *NewReg;
    pS = pBS->GetAt(i);
    NewReg = new CSample;
    for (int j=0; j < pS->m_Values.GetSize(); j++)
      NewReg->m_Values.Add(pS->m_Values.GetAt(j));
    m_pReguls.Add(NewReg);
  }

  theApp.CurrentTask|=OBJECT;
  InitTree(FALSE,1);
  CheckObject=FALSE;
  ForDefSmp();
  m_sStage.LoadString(IDS_TASK_DESC);
}

//------------------------------------------------------------------PrepareRec
void CScriptDoc::PrepareRec(int atr, int val)
{ CBV RecVect,RecRez;
  CBM Matr;
  if (!ToMatr(Matr)) return;
      
  ToVect(RecVect);
  ToVect(m_Vect);

  if (DirectContra(Matr,RecVect)) {
    CheckObject=TRUE;
    m_RowMask.Empty();
    m_RecMatr.SetSize(Matr.GetCountC(),Matr.GetCountC());
    m_RecMatr.Zero();
    m_nRecResult=Recogn(Matr,m_RecMatr,RecVect,RecRez,atr,val);
    m_nRecAtr = atr; m_nRecVal = val;
    if (m_nRecResult>=0) { 
      FromVect(RecRez); m_sStage.LoadString(IDS_REC_DONE); 
      m_Answer.Empty(); m_Answer = RecRez;
    }
    else {
      m_sStage.LoadString(IDS_L_CONTRADICT);
    }  
  }
  else { m_nRecResult=-1; CheckObject=FALSE; m_sStage.LoadString(IDS_L_CONTRADICT2);
  }
  ForDefSmp();
  UpdateAllViews(NULL);
}

//------------------------------------------------------------------ToVect
BOOL CScriptDoc::DirectContra(CBM& Matr,CBV& RecVect)
{ int i;
  BOOL Ret=TRUE;
  // 2007 m_RowMask.GetBufferSetLength(Matr.GetCountR()); m_RowMask.Zero();
  m_RowMask.SetSize(Matr.GetCountR());
  for (i=0; i<Matr.GetCountR(); i++)
    if (Matr.IsZero((const BYTE*)RecVect,i)) { m_RowMask.SetBitAt(i,1); Ret=FALSE; }
  return Ret;
}

//--------------------------------------------------------------------
void CScriptDoc::GetAim_ViewProof()
{ if (m_nRecResult<0) { //Proof contradict
    m_nRecAtr=m_nRecVal=-1;
    PrepareProof(m_nRecAtr,m_nRecVal); // Recognition is done
    return;
  }
 int w,j,k;
 CkAttr* pAttr;
 w = m_TreeRow.GetAt(m_ActDRow);
 j = LOBYTE(w); k = HIBYTE(w);
 pAttr = m_pAttrObj.GetAt(k);
  
  if (theApp.CurrentTask&AIM_FULL) {  // Full recognition
    if (pAttr->m_DFlag.GetBitAt(j)==0)
      if (m_Vect.GetBitAt(m_DomAdr[k]+j))
        PrepareProof(k,j);             // Proof recognition for value
      else AfxMessageBox("This value is impossible that follows from source object");
    else  PrepareProof(k,j);             // Proof recognition (valid set) for value 
  }
  else if (theApp.CurrentTask&AIM_ATR) {  // Attribute recognition
         if (m_nRecAtr!=k) { AfxMessageBox("Invalid attribute"); return; }
          if (pAttr->m_DFlag.GetBitAt(j)==0)
            if (m_Vect.GetBitAt(m_DomAdr[k]+j))
                PrepareProof(m_nRecAtr,-1); // Recognition is done
            else AfxMessageBox("This value is impossible that follows from source object");
          else    
             PrepareProof(m_nRecAtr,j);  // Recognition is done
       }
       else if (theApp.CurrentTask&AIM_VAL) {  // Value recognition
              PrepareProof(m_nRecAtr,m_nRecVal); // Recognition is done
            }
}




//------------------------------------------------------------------PrepareRec
void CScriptDoc::PrepareProof(int atr, int val)
{ CBV RecVect,RecRez;
  CString W,W1;
  int r,j,k,i,i1;
  m_MatrAndObj.RemoveAll();  m_Matr.RemoveAll();
  if (!ToMatr(m_Matr)) return;
  ToVect(m_Answer);
  m_MatrAndObj= m_Matr & m_Vect;
  
  if (atr!=-1 && val==-1) { // For attribute
    ToVect(RecVect); RecVect=m_Vect-RecVect;
    RecVect=MaskDom[atr]&RecVect;
    RecVect|=~MaskDom.GetRowBv(atr);
    for (r=0; r< m_MatrAndObj.GetCountR(); r++) {
      if (m_MatrAndObj.IsZero((const BYTE*)RecVect,r)) { // 0-proof for values
        m_sExplan.RemoveAll(); m_sExplanStep.RemoveAll();
        m_ActStep=r; m_NumStep=0;
        StringToArray(m_sExplan,Beg_z(5,atr,val,m_Vect));
        goto ww;
      }
    }
  }
  else           // For value
    if (atr!=-1) { // For attribute
      if (m_Answer.GetBitAt(m_DomAdr[atr]+val)==m_Vect.GetBitAt(m_DomAdr[atr]+val)) {
        // Valid set
        m_sExplan.RemoveAll(); m_sExplanStep.RemoveAll();
        m_ActStep=0; m_NumStep=0;
        StringToArray(m_sExplan,Beg_z(2,atr,val,m_Vect));
        goto ww;
      }  
      else {  
        RecVect=MaskDom.GetRowBv(atr);
        RecVect.SetBitAt(m_DomAdr[atr]+val,0);
        RecVect=~RecVect;
        for (r=0; r< m_MatrAndObj.GetCountR(); r++) {
          if (m_MatrAndObj.IsZero((const BYTE*)RecVect,r)) { // 0-proof for values
             m_sExplan.RemoveAll(); m_sExplanStep.RemoveAll();
             m_ActStep=r; m_NumStep=0;
             StringToArray(m_sExplan,Beg_z(3,atr,val,m_Vect));
             goto ww;
          }
        }
      }
    }
    else         // For contradict
      RecVect=m_Vect;
  m_Answer=RecVect;   
  if ((m_NumStep=Proof(m_MatrAndObj,RecVect,m_StepProof))<0) {
    AfxMessageBox(IDS_L_INFER_TOO_LONG); return;
  }
  
  if (atr==-1 && val==-1) r=4;
  else r=(val==-1)?6:0;
  StringToArray(m_sExplan,Beg_z(r,atr,val,m_Vect));
  m_ActStep=0;  GetStep(atr, val);
ww:  
  m_nRecAtr = atr; m_nRecVal = val;
  k = m_sExplan.GetSize();
  for (j=0; j < k; j++) {
    W = m_sExplan.GetAt(j);
    if (W.GetLength() > 90) {
      W1 = W;  r = i1 = 0;
      for (i=0; i<90; i++)
         if (W1[i] == '^') { i1 = i; r++; }
      if (r&1) {          // Split red color
        if (i1 == 0) {    // Length too large!!
          for (i=0; i<90; i++)       // Get last space
            if (W1[i] == ' ') i1 = i;
          W.SetAt(i1,'^');  
        }
        else if (i1 > 0 && W1[i1-1] == '(') i1--;
        
        m_sExplan.SetAt(j,W.Left(i1));
        m_sExplan.InsertAt(j+1,W.Right(W.GetLength()-i1));
        k++; continue;
      }   
      r = 0;
hod:      
      i=r + W1.FindOneOf("\n .,");
      if (i<r) continue;
      if (i > 90)
        if (r <= 0) continue;
        else {
          m_sExplan.SetAt(j,W.Left(r+1));
          m_sExplan.InsertAt(j+1,W.Right(W.GetLength()-r-1));
          k++; continue;
        }
      else { r = i+1;   W1 = W.Right(W.GetLength()-r-1); goto hod; }
    }
  }
  theApp.CurrentTask|=EXPLAN;
  CMainFrame* pFrameWnd = (CMainFrame*)theApp.m_pMainWnd;
  pFrameWnd-> CreateOrActivateFrame(theApp.pViewExplanTemplate, RUNTIME_CLASS(CExplanStepView));
  UpdateAllViews(NULL,NULL,NULL);
}



//------------------------------------------------------------------SplitRows
void CScriptDoc::SplitRows()   // For big string
{ int i,i1,j,k,r;
  CString W,W1;
 k = m_sExplanStep.GetSize();
 for (j=0; j < k; j++) {
  W = m_sExplanStep.GetAt(j);
  if (W.GetLength() > 90) {
    W1 = W; 
    r = 0;
hod:      
    i=r + W1.FindOneOf("\n .,");
    if (i<r) continue;
    if (i > 90)
      if (r <= 0) continue;
      else {
        W1 = W.Left(r+1);
        m_sExplanStep.SetAt(j,W1);
        i1 = 0;
        for (i=0; i<W1.GetLength(); i++)
         if (W1[i] == '^')  i1++; 
        if (i1&1)   W1 = "      ^";
        else        W1 = "      ";  
        W1 += W.Right(W.GetLength()-r-1);
        m_sExplanStep.InsertAt(j+1,W1);
        k++; continue;
      }
    else { r = i+1; W1 = W.Right(W.GetLength()-r-1); goto hod; }
  }
 }
}  
  
//------------------------------------------------------------------GetStep
void CScriptDoc::GetStep(int atr, int val) 
{ if (m_ActStep<m_NumStep-1) StringToArray(m_sExplanStep,if_4(m_MatrAndObj,m_ActStep));
  else             StringToArray(m_sExplanStep,Beg_z((val==-1)?9:7,atr,val,m_Vect));
  SplitRows();
}

//------------------------------------------------------------------StringToArray
void CScriptDoc::StringToArray(CStringArray& Arr,CString W)
{ int i;
  CString W1;
  Arr.RemoveAll();
  while (!W.IsEmpty()) {
    i = W.Find('\n');
    if (i<0) { Arr.Add(W); break; }
    W1= W.Left(i);Arr.Add(W1);
    W=W.Right(W.GetLength()-i-1);
  }
}

//------------------------------------------------------------------ToVect
void CScriptDoc::ToVect(CBV& Vect)
{ int i;
  CkAttr* pAttr;
  Vect.Empty();
  for (i=0; i<m_nDom; i++) {
    pAttr = m_pAttrObj.GetAt(i);
    Vect.Concat(pAttr->m_DFlag);
  }
}

//------------------------------------------------------------------FromVect
void CScriptDoc::FromVect(CBV& Vect)
{ int i;
  CkAttr* pAttr;
  for (i=0; i<m_nDom; i++) {
    pAttr = m_pAttrObj.GetAt(i);
    pAttr->m_DFlag = Vect.Extract(m_DomAdr[i],m_DomVal[i]);
  }
}

//------------------------------------------------------------------ToMatrCon
BOOL CScriptDoc::ToMatrCon(CBM& Matr)
{ int n,i;
  CSBlock* pBS;
  CSample *pSmp;
  
  if (!m_DBMap.Lookup((const char*) m_ActDB, pBS)) return FALSE;
  // Эта проверка непонятна для чего! (В принципе есть данные?)

  if (m_pSamples.GetSize())  m_pSamples.RemoveAll();
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
  Matr.SetSize(0,m_nValues);
  CBV Bv(0,m_nValues,1);
  for (n=0; n< m_pSamples.GetSize(); n++) {
    Bv.Zero();
    pSmp = m_pSamples.GetAt(n);
    for (i=0; i<m_nValues; i++)  // Circle for all attributes
      if (pSmp->m_Values[i])  Bv.SetBitAt(i,1);
    Matr.Add(Bv);
  }
  return TRUE;
}


//------------------------------------------------------------------ToMatr
BOOL CScriptDoc::ToMatr(CBM& Matr)
{ int n,Fl,nSave;
  int i,j,iS=0;
  CSBlock* pBS;
  CSample *pReg;

  if (!m_KBMap.Lookup((const char*) m_ActKB, pBS)) return FALSE;

  if (m_pReguls.GetSize())  m_pReguls.RemoveAll();
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

  Matr.SetSize(0,m_nValues);

  for (n=0; n< m_pReguls.GetSize(); n++) {
    CBV Bv;
    iS=0;
    pReg = m_pReguls.GetAt(n);

    for (i=0; i<m_nDom; i++) {  // Circle for all attributes
      CBV BvAtr(0,m_DomVal[i],TRUE);
      Fl=0; nSave=iS;
      for (j=0; j<(int)m_DomVal[i]; j++,iS++) {  // Circle for all values
        if (pReg->m_Values[iS]==2) { Fl=2; break;}
        else if (pReg->m_Values[iS]==1) Fl=1;
      }
      if (Fl==1) {        // Right part
        iS = nSave;
        for (j=0; j<(int)m_DomVal[i]; j++)   // Circle for all values
          if (pReg->m_Values[iS++]) BvAtr.SetBitAt(j,1);
      }
      else if (Fl==2) {
        iS = nSave;
        for (j=0; j<(int)m_DomVal[i]; j++)   // Circle for all values
          if (pReg->m_Values[iS++]==0) BvAtr.SetBitAt(j,1);
      }
      Bv.Concat(BvAtr); //afxDump << Bv; afxDump << "  \r\n";
    }
    Matr.Add(Bv);
  }
  return TRUE;
}

//------------------------------------------------------------------FromMatr
void CScriptDoc::FromMatr(CBM& Matr)
{ int i,j,k,n;
  CSample* pReg;
  if (m_pReguls.GetSize()) m_pReguls.RemoveAll();
  for (n=0; n<Matr.GetCountR(); n++) {
    pReg = new (CSample);
    for (i=0; i<m_nDom; i++)   // Circle for all attributes
      for (j=0; j<(int)m_DomVal[i]; j++) {  // Circle for all values
        k = Matr.GetBitAt(n,j+m_DomAdr[i]);
        pReg->m_Values.Add(k);
    }
    m_pReguls.Add(pReg);
  }
}

//------------------------------------------------------------------FromMatrDB
void CScriptDoc::FromMatrDB(CBM& Matr)
{ int i,j,k,n;
  CSample* pReg;
  if (m_pSamples.GetSize()) m_pSamples.RemoveAll();
  for (n=0; n<Matr.GetCountR(); n++) {
    pReg = new (CSample);
    for (i=0; i<m_nDom; i++)   // Circle for all attributes
      for (j=0; j<(int)m_DomVal[i]; j++) {  // Circle for all values
        k = Matr.GetBitAt(n,j+m_DomAdr[i]);
        pReg->m_Values.Add(k);
    }
    m_pSamples.Add(pReg);
  }
}

#endif //__MYLOCK


