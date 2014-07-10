// GenDat.cpp : implementation file
//
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "BaseBool.h"

CBM GenDat(int exp, int nRowD, CBM& MatrK);
CBM GenKnow(int exp, int nRowK, int Rang, int ver);
CBV CrRandVect(int ver);
BOOL CreateReg(int Rang,CBV& Row,CBV& Reg);  //FALSE - з-сть не построена

extern int nDoms;
extern CBM MaskDom;
extern vector<int>* DomVal;   //значность доменов
extern vector<int>* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

//------------------------------------------------------------- GenDat
//  √енераци€ секционированной матрицы данных
// ¬ход: 
//      exp   - номер эксперимента (сдвиг датчика случ.чисел)
//      nRowD - число строк в генерируемой матрице
//      MatrK - матрица знаний
// ¬ыход: 
//      MatrD - матрица данных
//-------------------------------------------------------------
CBM GenDat(int exp, int nRowD, CBM& MatrK)
{ int i,j,nRow,n=0;
  CBM MatrD;       
  CBV Row(0,MaskDom.GetCountC(),TRUE); 
  
  for(i=0; i<exp; i++)  j = rand();  //RAND_MAX 
  
  for(nRow=0; nRow<nRowD; nRow++)  {
gen: 
    if(n > 32000) break;
    n++;      Row.Zero();
    for(i=0; i<nDoms; i++) { // ѕостроение строки матрицы данных  
      j = rand() % (int)DomVal->at(i);
      Row.SetBitAt(j+(int)DomAdr->at(i),1);
    } 
    for(i=0; i<MatrK.GetCountR(); i++)   /*  ѕроверка на противоречие */ 
      if((MatrK[i] & Row).IsZero()) goto gen;   /* есть противоречие */
    MatrD.Add(Row);
  }
  return MatrD;  
}  

  
//------------------------------------------------------------- GenKnow
//  √енераци€ секционированной матрицы знаний
// ¬ход: 
//      exp   - номер эксперимента (сдвиг датчика случ.чисел)
//      ver   - веро€тность единичной компоненты в строке (в %)
//      Rang  - ранг закономерности (число св€занных признаков)
//      nRowK - число строк в генерируемой матрице
// ¬ыход: 
//      MatrK - матрица знаний
//-------------------------------------------------------------
CBM GenKnow(int exp, int nRowK, int Rang, int ver)
{ int i,j,nRow=0,n=0;
  CBM MatrK;
  CBV Row(0,MaskDom.GetCountC(),TRUE);
  CBV Reg(0,MaskDom.GetCountC(),TRUE);
  
//  if (Rang >= nDoms) return NULL;
  for(i=0; i<exp; i++)  j=rand();
  while (nRow < nRowK) {
    Row = CrRandVect(ver);     // ѕостроение вектора с плотностью ver распределени€ 1
    if (!CreateReg(Rang,Row,Reg)) continue;            // ѕостроение з-сти ранга Rang
    for(i=0; i<nRow; i++)  {
      if (MatrK[i] <= Reg) goto next;            // ѕроверка на поглощение  
    }
    MatrK.Add(Reg); nRow++;
next: n++; 
    if (n > 32000) break;
  }
  return MatrK;
}  
  
//-------------------------------------------------------------CreateVect
CBV CrRandVect(int ver)
{ int i,j,Max;
  CBV Row(0,MaskDom.GetCountC(),TRUE);
             
  Max = RAND_MAX/100*ver;
  for (i=0; i<MaskDom.GetCountC(); i++)  
    { j=rand(); if(j<=Max) Row.SetBitAt(i,1);}
  return Row;  
}


//-------------------------------------------------------------CreateReg
BOOL CreateReg(int Rang,CBV& Row,CBV& Reg)  //FALSE - з-сть не построена
{ int i,j;
  CBV Work(0,MaskDom.GetCountC(),TRUE);
  
  Reg.Zero();
  for (i=0; i<Rang; i++) {
    j=rand()%nDoms;    // номер выбранного домена
    Work = MaskDom.GetRowBv(j) & Row;
    if(Work == MaskDom[j]) return FALSE;
    if((Reg | Work) == Reg)  return FALSE;
    Reg |= Work;
  }
  return TRUE;  
}

