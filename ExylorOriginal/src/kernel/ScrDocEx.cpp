// scrdoc.cpp : implementation of the CExsDoc class
// 17.05.2007 -------------------------------------

#include "stdafx.h"
#include <io.h>
#include <ctype.h>
#include <sys\types.h>
#include <sys\stat.h>
#include "Exsylor.h"
#include "scrdoc.h"
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
// Work with explanation:
/////////////////////////////////////////////////////////////////////////////
//#include "SrcDocEx.cpp"

// Beg_z
// FormCon
// FormObj
// OneAttrib
// if_diz
// Diz_form
// if_4
// PutMatrixProof
// get_vct
// PutFormulaProof
// get_tx

/////////////////////////////////////////////////////////////////////////////
// Предъявление доказательства
// 18-05-2007 ---------------------------------------------------------------

/*--------------------------------------*/
/*  Prepare text of explanation BEG_Z   */
/*--------------------------------------*/
CString CScriptDoc::Beg_z(int n,int atr,int val, CBV& con)
/* n=0 - begin of value proof 1->0; 
   n=1 - explanation 1->1
   n=2 - explanation for valid value; 
   n=3 - 0-proof for value;
   n=4 - begin of contradiction with KB
   n=5 - 0-proof for attribute
   n=6 - begin of attribute proof
   n=7 - end of proof for globally
   n=8 - direct contrdictions ( absent)
   n=9 - end of proof
   n=10 - addition regularity
   n=11 - addition regularity
   atr,val - number of attribute and value */
{ int i,h,j;
  int k;                 // Get the data for the specific node.
  WORD w;
  char kst[5]; //,alf[5],set[400],buf5[400],pole[400],pole1[5];
  CString set,alf,buf5;
  CString buf;
  CkAttr* pAttr;  
  CString W,W1;
  CBV bv, bv0;
  Ins_txt.RemoveAll();
  if (atr>=0) {
    pAttr = m_pAttrObj.GetAt(atr);
    if (val>=0) // Values name
        Ins_txt.Add(pAttr->m_ValNames.GetAt(val));
    else  Ins_txt.Add("");
  
    if (atr>=0) // Attributes name
        Ins_txt.SetAtGrow(1,pAttr->m_sTitle);
    else  Ins_txt.SetAtGrow(1,"");
  }  
  
  Ins_txt.Add("");   //2   set
  Ins_txt.Add("");   //3   kst
  Ins_txt.Add("");   //4   alf
  Ins_txt.Add("");   //5   buf5
  Ins_txt.Add("");   //6   pole
  Ins_txt.Add("");   //7   pole1
  Ins_txt.Add("");   //8 
  Ins_txt.Add("");   //9   set
 
 switch(n) {
   case 0:     // Begin of proof for value
     itoa(m_NumStep,kst,10); W = kst; Ins_txt.SetAt(3,W);
     if (m_NumStep==1)  Ins_txt.SetAt(4,"");
     else             Ins_txt.SetAt(4,"s");
          
     get_tx(IDS_L_NOT_VAL,buf); get_tx(IDS_L_NOT_VAL_1,buf); get_tx(IDS_L_NOT_VAL_2,buf);
     get_tx(IDS_L_LEN_PROOF,buf);
     break;

//   case 1: get_tx(4,buf); break; -------------------------------absent

   case 2:     // Valid set for value
     W ="";
     bv = m_RecMatr.GetRowBv(m_DomAdr[atr]+val);
     
     for (i=0; i<m_nDom; i++)  { 
       pAttr = m_pAttrObj.GetAt(i);
       W+="(^"; W += pAttr->m_sTitle + " - ";
       for (j=0; j<(int)m_DomVal[i]; j++)
         if (bv.GetBitAt(m_DomAdr[i]+j)) break;
       if (j== (int)m_DomVal[i]) { W1.LoadString(IDS_ANY_VAL);W+=W1+"^), "; }
       else  W+=pAttr->m_ValNames.GetAt(j)+"^), ";
     }
     W = W.Left(W.GetLength()-2); Ins_txt.SetAt(2,W);
     get_tx(IDS_L_VALID_SET,buf); break;

   case 3:      // 0-proof for value
     itoa(m_ActStep,kst,10); W = kst; Ins_txt.SetAt(3,W);
     bv = m_Matr.GetRowBv(m_ActStep);
     W=""; bv0.Empty(); bv0=m_Answer; m_Answer = bv;
     if_diz(bv,W); Ins_txt.SetAt(2,W); m_Answer = bv0;
     FormObj(W); Ins_txt.SetAt(4,W);
     get_tx(IDS_L_0_PROOF_VAL,buf); get_tx(IDS_L_0_PROOF_VAL2,buf);
     break;

   case 4:      // Begin proof for contradiction
     itoa(m_NumStep,kst,10); W = kst; Ins_txt.SetAt(3,W);
     if (m_NumStep==1)  Ins_txt.SetAt(4,"");
     else               Ins_txt.SetAt(4,"s");
     FormCon(W);      Ins_txt.SetAt(2,W);
     get_tx(IDS_L_PROOF_CONTRA,buf);
     get_tx(IDS_L_PROOF_CONTRA_1,buf);
     get_tx(IDS_L_LEN_PROOF,buf);
     break;

  case 5:    //// 0-proof for attribute
     h=0;W=""; w = m_TreeRow.GetAt(m_ActDRow); j = LOBYTE(w); k = HIBYTE(w);
     pAttr = m_pAttrObj.GetAt(k);
     bv0 =  m_Vect.Extract(m_DomAdr[k], m_DomVal[k]);
     bv0 ^=pAttr->m_DFlag;
     for (j=0; j<(int)m_DomVal[k]; j++)
       if (bv0.GetBitAt(j)) { h++; W+=pAttr->m_ValNames.GetAt(j)+", "; }
     W = W.Left(W.GetLength()-2); Ins_txt.SetAt(5,W);
     if (h==1) { Ins_txt.SetAt(4,""); Ins_txt.SetAt(6,"is");}
     else      { Ins_txt.SetAt(4,"s"); Ins_txt.SetAt(6,"are");}
     
     itoa(m_ActStep,kst,10); W = kst; Ins_txt.SetAt(3,W);
     bv = m_Matr.GetRowBv(m_ActStep);
     W=""; bv0.Empty(); bv0=m_Answer; m_Answer = bv;
     if_diz(bv,W); Ins_txt.SetAt(2,W); m_Answer = bv0;
     FormObj(W); Ins_txt.SetAt(7,W);
     get_tx(IDS_L_0_PROOF_ATR,buf); break;

   case 6:   // Begin proof for attribute
     h=0;W=""; w = m_TreeRow.GetAt(m_ActDRow); j = LOBYTE(w); k = HIBYTE(w);
     pAttr = m_pAttrObj.GetAt(k);
     bv0 =  m_Vect.Extract(m_DomAdr[k], m_DomVal[k]);
     bv0 ^=pAttr->m_DFlag;                             // List new 0-value in k-atr
     for (j=0; j<(int)m_DomVal[k]; j++)
       if (bv0.GetBitAt(j)) { h++; W+=pAttr->m_ValNames.GetAt(j)+", "; }
     W = W.Left(W.GetLength()-2); Ins_txt.SetAt(5,W);
     if (h==1) { Ins_txt.SetAt(4,""); Ins_txt.SetAt(6,"is");}
     else      { Ins_txt.SetAt(4,"s"); Ins_txt.SetAt(6,"are");}
     W="^";
     for (j=0; j<(int)m_DomVal[k]; j++)
       if (bv0.GetBitAt(j)) { W+=pAttr->m_ValNames.GetAt(j)+"^ or ^"; }
     W = W.Left(W.GetLength()-5); Ins_txt.SetAt(2,W);
     get_tx(IDS_L_PROOF_ATR0,buf);
     get_tx(IDS_L_NOT_VAL_1,buf);
     itoa(m_NumStep,kst,10); W = kst; Ins_txt.SetAt(3,W);
     if (m_NumStep==1)  Ins_txt.SetAt(4,"");
     else             Ins_txt.SetAt(4,"s");
     get_tx(IDS_L_LEN_PROOF,buf); break;

   case 7:  
     h=0;W="";
     //w = m_TreeRow.GetAt(m_ActDRow); j = LOBYTE(w); k = HIBYTE(w);
     //pAttr = m_pAttrObj->GetAt(k);
     //bv0 =  m_Vect.Extract(m_DomAdr[k], m_DomVal[k]);
     //bv0 ^=pAttr->m_DFlag;
     //for (j=0; j<(int)m_DomVal[k]; j++)
//       if (bv0.GetBitAt(j)) { h++; W+=pAttr->m_ValNames.GetAt(j)+" or "; }
  //   W = W.Left(W.GetLength()-4); Ins_txt.SetAt(5,W);
    // if (h==1) { Ins_txt.SetAt(4,""); Ins_txt.SetAt(6,"is");}
    // else      { Ins_txt.SetAt(4,"s"); Ins_txt.SetAt(6,"are");}
     
     itoa(m_StepProof[m_StepProof.GetUpperBound()-3],kst,10); W = kst; Ins_txt.SetAt(5,W);
     itoa(m_StepProof[m_StepProof.GetUpperBound()-2],kst,10); W = kst; Ins_txt.SetAt(3,W);
     bv = m_MatrAndObj.GetRowBv(m_StepProof[m_StepProof.GetUpperBound()-3]);
     W=""; if_diz(bv,W); Ins_txt.SetAt(6,W);
     bv.Empty();
     bv = m_MatrAndObj.GetRowBv(m_StepProof[m_StepProof.GetUpperBound()-2]);
     W=""; if_diz(bv,W); Ins_txt.SetAt(2,W);     //if_diz(con,pole); if_diz(vec,set);
     get_tx(IDS_L_STATEM,buf);
     get_tx(IDS_L_STATEM_3,buf);
     break;
/*                              ------------------------------ absent
   case 8: itoa(kol_step,kst,10);
#ifndef ENG
     if (kol_step%10==1 && kol_step%100!=11) strcpy(alf,"е");
     else
       if (kol_step%10>4 || kol_step%100>9 && kol_step%100<21) 
         strcpy(alf,"й");
       else strcpy(alf,"я");
#else
     if (kol_step%10==1 && kol_step%100!=11) alf[0]=0;
     else                     strcpy(alf,"s");
#endif
     get_tx(13,buf); break;
*/
   case 9:    // End of proof for contradiction
     itoa(m_StepProof[m_StepProof.GetUpperBound()-3],kst,10); W = kst; Ins_txt.SetAt(5,W);
     itoa(m_StepProof[m_StepProof.GetUpperBound()-2],kst,10); W = kst; Ins_txt.SetAt(3,W);
     bv = m_MatrAndObj.GetRowBv(m_StepProof[m_StepProof.GetUpperBound()-3]);
     W=""; if_diz(bv,W); Ins_txt.SetAt(6,W);
     bv.Empty();
     bv = m_MatrAndObj.GetRowBv(m_StepProof[m_StepProof.GetUpperBound()-2]);
     W=""; if_diz(bv,W); Ins_txt.SetAt(2,W);     //if_diz(con,pole); if_diz(vec,set);
     
     get_tx(IDS_L_STATEM,buf);
     get_tx(IDS_L_STATEM_4,buf); 
     //if (task==8 && ret_cod==1) i=IDS_L_STATEM_6;
     //else  if (task == 8) i=IDS_L_STATEM_5;  else i=IDS_L_STATEM_4;
     //get_tx(i,buf);
     break;
     
/*                              ------------------------------ absent
   case 10: vect_msk(con,mask1); itoa(kol_step,kst,10);
     if (kol_step%10==1&& kol_step%100!=11)  alf[0]='\0';
     else       strcpy(alf,"s");
     FormCon(W); // set[0] = '\0'; form_con(set,mask1);
     get_tx(ret_cod==1 ? 17:15,buf); j = strlen(buf); buf[j] = '\n';
     if (ret_cod==2) 
       { get_tx(10,buf+j+1); j = strlen(buf); buf[j] = '\n'; }
     get_tx(11,buf+j+1); break;

   case 11: itoa(zakon,kst,10); set[0] = '\0'; task=4;
     if_diz(matr_d+(zakon-1)*len_str,set);
     get_tx(19,buf); task=8; break;
  }
-------------------------------------------------------------------*/  
  //h = f_text(buf,l-3); 
  // .... display
  }
  return(buf);
}

//-------------------------------------------------------------
void  CScriptDoc::FormCon(CString& W)
{ int i,j;
 CkAttr* pAttr;  
 CString W1;
 W=""; 
 for (i=0; i<m_nDom;  i++,W+=" and ")  { 
   pAttr = m_pAttrObj.GetAt(i);
   if ((j=pAttr->m_DFlag.CountBit())==0) continue;
   if (j==(int)m_DomVal[i]) 
     { W1.LoadString(IDS_ANY_VAL);W+="^"+pAttr->m_sTitle; W+=" - "+W1; W+="^"; continue; }
   OneAttrib(W,pAttr->m_DFlag,pAttr, j);
 }
 W = W.Left(W.GetLength()-5);
}

//-------------------------------------------------------------
void  CScriptDoc::FormObj(CString& W)
{ int i,j;
 CkAttr* pAttr;  
 CString W1;
 W=""; 
 for (i=0; i<m_nDom;  i++,W+=" and ")  { 
   CBV bv;
   pAttr = m_pAttrObj.GetAt(i);
   bv = m_Vect.Extract(m_DomAdr[i],m_DomVal[i]);
   if ((j=bv.CountBit())==0) continue;
   if (j==(int)m_DomVal[i]) 
     { W1.LoadString(IDS_ANY_VAL);W+="^"+pAttr->m_sTitle; W+=" - "+W1; W+="^"; continue; }
   OneAttrib(W,bv,pAttr, j);
 }
 W = W.Left(W.GetLength()-5);
}


//-------------------------------------------------------------
void CScriptDoc::OneAttrib(CString& W,CBV& bv,CkAttr* pAttr, int j)
{ CString W1;
 W+="^"+pAttr->m_sTitle; W+=" - ";
 if (j==1) {
   for (j=0; j<bv.GetBitLength(); j++) if (bv.GetBitAt(j)) break;
   W+=pAttr->m_ValNames.GetAt(j); W+="^"; return;
 }  
 if (j==bv.GetBitLength()-1) {
   W+="not ";
   for (j=0; j<bv.GetBitLength(); j++) if (!bv.GetBitAt(j)) break;
   W+=pAttr->m_ValNames.GetAt(j); W+="^"; return;  
 }
 for (j=0; j<bv.GetBitLength(); j++) if (bv.GetBitAt(j)) W+=pAttr->m_ValNames.GetAt(j)+" or ";  
 W = W.Left(W.GetLength()-4); W+="^";
}

/*************************************************/
/*  Программа построения формулы для дизъюнкта   */
/*                     IF_DIZ                    */
/**11-04-92 07:39pm*******************************/
//----------------------------------------------------------------------
//  IF_DIZ
//----------------------------------------------------------------------
void CScriptDoc::if_diz (CBV& vect,CString& form)      /* дизъюнкт */
{ int i,i1,i2=-1,j,zer,one,min;
  CBV msk(vect);
  CBV Wbv,Wbv0;
  CkAttr* pAttr;  
  CString s;
 // msk=malloc(numb_pr*2);  vect_msk (vect,msk); s[0]='\0'; min=16;
 /* преобразование маски */
 msk&=m_Answer;
 min = 32;
 for (j=i=0; i<m_nDom; i++) {      /* подсчет ненулевых доменов */
   Wbv = msk & MaskDom[i]; if (!Wbv.IsZero()) { j++; i1=i; }
 }  
 if (j==1) {  /*  построение простой формулы */ 
  pAttr = m_pAttrObj.GetAt(i1);
  Wbv = msk & MaskDom[i1]; 
  Wbv0 = Wbv.Extract(m_DomAdr[i1],m_DomVal[i1]);
  j =Wbv0.CountBit();
  OneAttrib(form,Wbv0,pAttr, j);
  return;
 }
 for (i=0; i<m_nDom; i++)  {  /* поиск оптимального конъюнкта */
   Wbv = msk & MaskDom[i]; one=Wbv.CountBit(); /* число единиц */
   if (one==0) continue;
   if ((int)m_DomVal[i] == one+1){  /*  есть только 1 нуль */
     for (j=0; j<(int)m_DomVal[i]; j++)
       if (msk.GetBitAt(m_DomAdr[i]+j)==0) break;    /* j - позиция "0" */
     Wbv = msk & ~MaskDom.GetRowBv(i);
     s="";
     Diz_form(Wbv,i,j,s,form); return;
   }
   if (one == 1) {  /* есть только 1 единица */
     s="Not ";                     //get_btx(3,7));           /* BTX */
     for (j=0; j<(int)m_DomVal[i]; j++)
       if (msk.GetBitAt(m_DomAdr[i]+j)==1) break;    /* j - позиция "1" */
     Wbv = msk & ~MaskDom.GetRowBv(i);
     Diz_form(Wbv,i,j,s,form); return;
   }
   zer=m_DomVal[i]-one;                           /* число нулей */
   if (min>zer) { min=zer; i2=i;}
 } /* конец поиска */
 if (i2>=0) { j=100; s=""; Diz_form (msk,i1,j,s,form);}  
 return;
}

/*--------------------------------------*/
/*  Функция построения длинной формулы  */
/*              DIZ_FORM                */
/*--------------------------------------*/

void CScriptDoc::Diz_form (CBV& msk, int i, int j, CString s,CString& form)
        /* номер признака для конъюнкта *//* номер "1" или "0" в маске    */
        /* "не" или " " *//*  для формулы */
{ int i1;
  CkAttr* pAttr;  
  CBV Wbv,Wbv0;
  pAttr = m_pAttrObj.GetAt(i);
  form +="If ";            /* BTX get_btx(3,14)*/
  if (j<100) { /* простой конъюнкт */
    form+="^"+pAttr->m_sTitle; form+=" - "+s;
    form+=pAttr->m_ValNames[j]+ "^, then ";   /* BTX get_btx(3,15))*/
  }
  else      { /* длинный конъюнкт */
    Wbv0 = msk.Extract(m_DomAdr[i],m_DomVal[i]);
    Wbv0 = ~Wbv0;  j =Wbv0.CountBit();
    OneAttrib(form,Wbv0,pAttr, j);
    form+=", then ";           /* BTX get_btx(3,16)*/
    msk &= ~MaskDom.GetRowBv(i);
  }
/*   Построение правой части формулы */
  for (i1=0; i1<m_nDom; i1++) {
    Wbv = msk & MaskDom[i1]; 
    if (Wbv.IsZero()) continue;
    pAttr = m_pAttrObj.GetAt(i1);
    Wbv0.Empty();
    Wbv0 = Wbv.Extract(m_DomAdr[i1],m_DomVal[i1]);
    j =Wbv0.CountBit();
    OneAttrib(form,Wbv0,pAttr, j);
    form+=" or ";            /* BTX get_btx(3,10)*/
  }
  form = form.Left(form.GetLength()-4); return;
}

//---------------------------------------------------------
// IF_4: matr- M&Object, i- number of step
//---------------------------------------------------------
CString CScriptDoc::if_4(CBM matr,int i) 
{ char buf[100];
  CBV Wbv; 
  CString form;
 form="Step ";                                                     /* BTX get_btx(3,1)*/
 itoa(i+1,buf,10); form+=buf; form+=": from (";                    /* BTX get_btx(3,2)*/
 itoa(m_StepProof[i*4],buf,10);  form+=buf; form+=") and (";       /* BTX get_btx(3,3)*/
 itoa(m_StepProof[i*4+1],buf,10);  form+=buf; form+=") follows ("; /* BTX get_btx(3,4)*/
 itoa(m_StepProof[i*4+3],buf,10);  form+=buf;form+=")\n";
 itoa(m_StepProof[i*4],buf,10); form+=" ("; form+=buf; form+="): ";
 Wbv = matr.GetRowBv(m_StepProof[i*4]);
 if_diz(Wbv,form);
 form+=",\n ("; itoa(m_StepProof[i*4+1],buf,10); form+=buf; form+="): ";
 Wbv = matr.GetRowBv(m_StepProof[i*4+1]);
 if_diz(Wbv,form);
 form+=",\n =======================================\n ("; /* BTX get_btx(3,5)*/
 itoa(m_StepProof[i*4+3],buf,10); form+=buf; form+="): ";
 Wbv = matr.GetRowBv(m_StepProof[i*4+3]);
 if_diz(Wbv,form); 
 return (form);
}

//------------------------------------------------------------------PutMatrixProof
/*-----------------------------------------------------------*/
/*  Доказательство шага логического вывода в векторной форме */
/*-----------------------------------------------------------*/
void CScriptDoc::PutMatrixProof()
{ char buf[16];
 CString form;
 CBV Wbv;
 form="Step ";                                                             /* BTX get_btx(3,1)*/
 itoa(m_ActStep+1,buf,10); 
 form+=buf; form+=": from (";                    /*  BTX get_btx(3,2)*/
 itoa(m_StepProof[m_ActStep*4],buf,10); 
 form+=buf; form+=") and (";       /* BTX get_btx(3,3)*/
 itoa(m_StepProof[m_ActStep*4+1],buf,10);
 form+=buf; form+=") follows ("; /* BTX get_btx(3,4)*/
 itoa(m_StepProof[m_ActStep*4+3],buf,10);
 form+=buf; form+=")\n";
 //itoa(m_StepProof[m_ActStep*4],buf,10); 
 sprintf(buf,"%03u",m_StepProof[m_ActStep*4]);
 form+=" ("; form+=buf; form+="): ";
 Wbv = m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4]);
 Wbv&=m_Answer;
 get_vct(form,Wbv,m_StepProof[m_ActStep*4+2]);
 
 form+=",\n ("; 
 //itoa(m_StepProof[m_ActStep*4+1],buf,10); 
 sprintf(buf,"%03u",m_StepProof[m_ActStep*4+1]);
 
 form+=buf; form+="): ";
 Wbv = m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4+1]);
 Wbv&=m_Answer;
 get_vct(form,Wbv,m_StepProof[m_ActStep*4+2]);
 
 form+=",\n ==============================================================================\n ("; /* BTX get_btx(3,5)*/
 //itoa(m_StepProof[m_ActStep*4+3],buf,10); 
 sprintf(buf,"%03u",m_StepProof[m_ActStep*4+3]);
 form+=buf; form+="): ";
 Wbv = m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4+3]);
 Wbv&=m_Answer;
 get_vct(form,Wbv,m_StepProof[m_ActStep*4+2]);
 
 StringToArray(m_sExplanStep,form);
 UpdateAllViews(NULL,NULL,NULL);
}

/********************************************************/
void CScriptDoc::get_vct(CString& form,CBV& vct0,int pr)
{ int k;
  for (k=0; k<m_nDom; k++) {
    CBV bv;
    bv=vct0.Extract(m_DomAdr[k],m_DomVal[k]);
    if (pr==k) form +="^";
    form += bv.BitChar('1','0')+" "; 
    if (k==pr) form +="^";
  }  
  return;
}

/*------------------------------------------*/
/*  Доказательство шага логического вывода  */
/*------------------------------------------*/
void CScriptDoc::PutFormulaProof()
{ CBV msk1,msk2,msk;
   int j,s1,s2,glob;
  char buf0[10];
  CkAttr* pAttr;  
  CBV Wbv,Wbv0;
  CString buf,form;
  glob = m_StepProof[m_ActStep*4+2];
 pAttr = m_pAttrObj.GetAt(glob);
 
 form.LoadString(IDS_L_PROOF_ADD);      /* BTX get_btx(3,6) */
 itoa(m_StepProof[m_ActStep*4],buf0,10);  form+=buf0; form+="): ";
 msk1= m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4]);
 msk=msk1.Extract(m_DomAdr[glob],m_DomVal[glob]);

 for (s1=j=0; j<m_nDom; j++)
   { Wbv = msk1 & MaskDom[j]; if (!Wbv.IsZero()) s1++; }
 j =msk.CountBit();  
 if (s1==1 && j) { OneAttrib(form,msk,pAttr,j); goto rfi0; }
 if (j+1==(int)m_DomVal[glob]) {  /*  есть только 1 нуль */
   for (j=0; j<(int)m_DomVal[glob]; j++)
     if (msk.GetBitAt(j)==0) break;    /* j - позиция "0" */
   msk1 &= ~MaskDom.GetRowBv(glob);
   buf=""; Diz_form(msk1,glob,j,buf,form); goto rfi0;
 }
 if (j == 1) {  /* есть только 1 единица */
   buf="Not ";                     //get_btx(3,7));           /* BTX */
   for (j=0; j<(int)m_DomVal[glob]; j++)
     if (msk.GetBitAt(j)==1) break;    /* j - позиция "1" */
   msk1 &= ~MaskDom.GetRowBv(glob);
   Diz_form(msk1,glob,j,buf,form); goto rfi0;
 }
 buf=""; Diz_form(msk1,glob,100,buf,form);

rfi0:
 
 msk1= m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4]);
 form+=",\n(";  itoa(m_StepProof[m_ActStep*4+1],buf0,10); form+=buf0; form+="): ";
 msk2= m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4+1]);
 
 msk=msk2.Extract(m_DomAdr[glob],m_DomVal[glob]);
 
 for (s2=j=0; j<m_nDom; j++)
   { Wbv = msk2 & MaskDom[j]; if (!Wbv.IsZero()) s2++; }
 j =msk.CountBit();  
 if (s2==1 && j) { OneAttrib(form,msk,pAttr,j); goto rfi; }
 if (j+1==(int)m_DomVal[glob]) {  /*  есть только 1 нуль */
   for (j=0; j<(int)m_DomVal[glob]; j++)
     if (msk.GetBitAt(j)==0) break;    /* j - позиция "0" */
   msk2 &= ~MaskDom.GetRowBv(glob);
   buf=""; Diz_form(msk2,glob,j,buf,form); goto rfi;
 }
 if (j == 1) {  /* есть только 1 единица */
   buf="Not ";                     //get_btx(3,7));           /* BTX */
   for (j=0; j<(int)m_DomVal[glob]; j++)
     if (msk.GetBitAt(j)==1) break;    /* j - позиция "1" */
   msk2 &= ~MaskDom.GetRowBv(glob);
   Diz_form(msk2,glob,j,buf,form); goto rfi;
 }
 buf=""; Diz_form(msk2,glob,100,buf,form);

rfi:  msk2= m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4+1]);
 if (s1==1 && s2==1) { buf.LoadString(IDS_L_PROOF_ADD3); form+=buf; return; }  /* BTX get_btx(1,6)*/
 if (s1==1 || s2==1) { 
   buf.LoadString(IDS_L_PROOF_ADD0); form+=buf;   /* BTX get_btx(3,8)*/
   form+="       "; msk1 &= ~MaskDom.GetRowBv(glob); goto rf4;
 }
 buf.LoadString(IDS_L_PROOF_ADD1);  form+=buf;    /* BTX get_btx(3,9)*/
 form+="       ";
 
 Wbv =(msk1&msk2)&MaskDom.GetRowBv(glob);
 if (Wbv.IsZero()) {  /* Полная система посылок */
   if (s1!=1) Wbv = msk1^MaskDom.GetRowBv(glob);
   else       Wbv = msk1;
   Wbv0.Empty();
   Wbv0 = Wbv.Extract(m_DomAdr[glob],m_DomVal[glob]);
   j = Wbv0.CountBit();
   OneAttrib(form,Wbv0,pAttr,j);
   form+=" or ";                                      /* BTX get_btx(3,10)*/
   
   if (s2!=1) Wbv = msk2^MaskDom.GetRowBv(glob);
   else       Wbv = msk1;
   Wbv0.Empty();
   Wbv0 = Wbv.Extract(m_DomAdr[glob],m_DomVal[glob]);
   j = Wbv0.CountBit();
   OneAttrib(form,Wbv0,pAttr,j);
   msk1 &= ~MaskDom.GetRowBv(glob);
 }  /* Конец обработки полной системы посылок */
 else {
   msk1|= Wbv;
   form+="^"+pAttr->m_sTitle; form+="^ - ^";
   for (j=0; j<(int)m_DomVal[glob]; j++)
     { form+=pAttr->m_ValNames.GetAt(j); form+="^ or ^";} /* BTX */
   form=form.Left(form.GetLength()-5);
 }
 form+=",\n then\n       ";                     /* BTX get_btx(3,12) */

rf4: msk2 &= ~MaskDom.GetRowBv(glob); msk1 |= msk2;       /*  склеивание масок  */
 for(j=0; j<m_nDom; j++) {
   Wbv0.Empty();
   Wbv0 = msk1.Extract(m_DomAdr[j],m_DomVal[j]);
    if (!Wbv0.IsZero()) {
      pAttr = m_pAttrObj.GetAt(j);
      s1 = Wbv0.CountBit();  OneAttrib(form,Wbv0,pAttr,s1);
      form+=" or ";          /* BTX get_btx(3,10)*/
    }
 }
 
 form=form.Left(form.GetLength()-4); //????? form[strlen(form)-5]='\0';
 buf.LoadString(IDS_L_PROOF_ADD2); form+=buf;       /* BTX get_btx(3,13)*/
 itoa(m_StepProof[m_ActStep*4+3],buf0,10); form+=buf0;
 form+="): ";
 Wbv = m_MatrAndObj.GetRowBv(m_StepProof[m_ActStep*4+3]);
 if_diz(Wbv,form);   form+="."; 
 StringToArray(m_sExplanStep,form); SplitRows();
 UpdateAllViews(NULL,NULL,NULL);
 return;
}

/*---------------------------------------------------*/
/*   Программа построения размеченного текста GET_TX */
/*---------------------------------------------------*/
void get_tx (int numb_txt,CString& Txt)
     /* Номер размеченного текста - поле для текста  */
     /*Ins_txt[] - Указатели на вставляемые фрагменты */
     /*text -  Размеченные тексты -kat[] - Каталог размеченных текстов */
{ int i,j=0,end,n;
  CString text;                       /* BTX */
  text.LoadString(numb_txt);
  
  i=0; end=text.GetLength();
  while (i<end) {
    if (text[i]=='~') 
      { i++; n=text[i]&15; Txt+=Ins_txt[n];}
   else Txt += text[i];
   i++;
 }
 return;
}

