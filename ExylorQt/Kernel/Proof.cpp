// GenDat.cpp : implementation file
// 18.05.2007 -----------------------

#include "stdafx.h"
#include "exsylor.h"
#include "coverDoc.h"

int Proof(CBM& Matr,CBV& VectRec,CWordArray& StepProof);
BOOL BuildChainProof(CBM& SDiz,CBV& VectRec,CStack& Chain);
int BuildStepsProof(CBM& SDiz, CBV& MaskC,CStack& Chain, CWordArray& StepPrf);
BOOL BuildNewStep(CBM& SDiz,CBV& MaskCol,struct pr *Proof,CWordArray& StepProof);

extern int nDoms;
extern CBM MaskDom;
extern CWordArray* DomVal;   //значность доменов
extern CWordArray* DomAdr;   //адреса доменов в строке (nDom+1 элементов)


//-------------------------------------------------------------BuildChainProof
//  Построение доказательства невыполнимости матрицы
//  Выход: 
//        -1 - матрица SDiz выполнима
//        -2 - число шагов доказательства > MaxStep
//         n - число шагов доказательства
//         последние n строк матрицы Matr содержат доказательство
//-------------------------------------------------------------
#define MaxStep 100

int Proof(CBM& Matr,CBV& VectRec,CWordArray& StepProof)
{ int nStep;
  CStack Chain;
 StepProof.RemoveAll();
 if (BuildChainProof(Matr,VectRec,Chain) == FALSE) nStep = -1;
 else 
  nStep = BuildStepsProof(Matr,VectRec,Chain,StepProof); 
 return nStep;
}


//-------------------------------------------------------------BuildChainProof
//  Построение цепочки для доказательства невыполнимости матрицы
//  Выход: 
//        FALSE - матрица SDiz выполнима
//        Chain - обратная цепочка док-ва
//-------------------------------------------------------------
BOOL BuildChainProof(CBM& SDiz,CBV& VectRec,CStack& Chain)
{ int i,nRow,nd=0,nc,Fl;

 CBM tm(SDiz,FALSE);                // Построение транспонированной матрицы
 CBV MaskCol(VectRec);
 nRow = SDiz.GetCountR();
 CBV MaskRow(1,nRow,TRUE);
 CBM StepMaskRow(nDoms,nRow);      //м-ца масок строк при ветвлении
 CBM StepMaskCol(nDoms,SDiz.GetCountC());    //м-ца масок столбцов при ветвлении
 CBV Work;
 CBV Mask;
 CWordArray Wdom;                   //массив весов домена с учетом MaskCol
 CWordArray Wrow;                   //массив весов строк с учетом MaskCol
 CWordArray NumbV;                  //массив числа ветвлений по каждому домену 
 CWordArray NumbCol;                //массив номеров столбцов при ветвлении 
 Wdom.SetSize(nRow);    Wrow.SetSize(nRow); 
 NumbV.SetSize(nDoms); NumbCol.SetSize(nDoms);
 for (i=0; i<nDoms; i++) { NumbV[i]=0; NumbCol[i]=-1; }
  
 RedCols(tm,MaskRow,MaskCol);            //Редукция (поглощение столбцов внутри домена)
 FindColsZero(tm,MaskRow,MaskCol);       //Исключение пустых столбцов

//----------------------------------Построение массива весов доменa nd с учетом MaskCol
step1: Fl=0;
 Mask = MaskCol & MaskDom[nd];
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   Work = SDiz[i] & MaskCol;    Wrow[i]= Work.CountBit();
   if (Wrow[i] == 0) { Fl=1; break; }                   //тупик
   Work = SDiz[i] & Mask;       Wdom[i]= Work.CountBit();
 }
 if (Fl) { 
   Chain.Push(i);  Chain.Push(-3);  //запись в стек 1)номер строки, 2)'-'(-3)
   if (nd) goto next;
   goto fin;
 }
 
//-----------------------------------------------------------Выбор строки для покрытия
 Fl=0; 
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   if (Wdom[i] > 1) continue;
   if (Wrow[i] == 1) { Fl=1; break; }
 }
 if (Fl) { 
   if (Wdom[i] == 0) {
     nc = (SDiz[i] & MaskCol).LeftOne();
     nd = ComputeNomDom(nc);         //Опр-ние N домена по N столбца в строке
   }  
   Chain.Push(i); Chain.Push(nd);  //запись в стек 1)номер строки, 2)номер домена
   Work = SDiz[i] & MaskCol & MaskDom[nd];
   nc = Work.LeftOne();
 }
 else     {
   Work = MaskCol & MaskDom[nd];
   NumbV[nd] = Work.CountBit();             //число ветвлений
   Chain.Push(-1);  Chain.Push(NumbV[nd]);  //запись в стек 1)'+', 2)число ветвлений
   Chain.Push(nd);  Chain.Push(-2);         //запись в стек 3)номер домена, 4)':'
   nc = Work.LeftOne();
   StepMaskRow.SetRow(nd, MaskRow);
   StepMaskCol.SetRow(nd, MaskCol);
   NumbCol[nd] = nc;   
 }
//------------------------------------------------------Корректировка MaskRow, MaskCol
step2: 
 MaskCol &= ~MaskDom.GetRowBv(nd);  MaskRow &= ~tm.GetRowBv(nc);
 if (MaskRow.IsZero()) return FALSE;
 if ((i=MaskCol.LeftOne()) >=0) {
   nd = ComputeNomDom(i);         //Опр-ние N домена по N столбца в строке
   goto step1;
 }  
 i = MaskRow.LeftOne();
 Chain.Push(i);  Chain.Push(-3);  //запись в стек 1)номер строки, 2)'-'(-3)

//------------------------------------------------Определение очередного номера домена
next:  
  for (i=nDoms-1; i>=0; i--) {
    if (NumbV[i] == 0) continue;
    if (--NumbV[i]==0) continue; 
    nd = i;
    MaskRow = StepMaskRow[nd];
    MaskCol = StepMaskCol[nd];
    Work = MaskCol & MaskDom[nd];
    nc = Work.LeftOne((int)NumbCol[nd]);
    NumbCol[nd] = nc;
    goto step2;
  }
fin:
 Wdom.RemoveAll();   Wrow.RemoveAll();  
 NumbV.RemoveAll();  NumbCol.RemoveAll();
 return TRUE;  
}

//------------------------------------------------------------BuildStepsProof
//  Построение шагов доказательства невыполнимости матрицы
//  Вход: 
//      SDiz  - исходная матрица
//      Chain - стек, содержащий цепочку для построения док-ва
//  Выход: 
//      nStep - число шагов доказательства,
//              или -2 при nStep > MaxStep
//      SDiz  - исходная матрица + nStep строк доказательства
//  StepProof - массив (nStep х 4): 1)NomR1, 2)NomR2, 3)NomDom, 4)NomRez
//----------------------------------------------------------------------
int BuildStepsProof(CBM& SDiz, CBV& MaskCol,CStack& Chain, CWordArray& StepProof)
{ int nStep=0;
  WORD NumbV,st;
  CStack NomRow;             //рабочий стек номеров строк при построении док-ва 
  struct pr Proof;
  
 while (Chain.Pop(st))   { //стек Chain не пуст
sw: 
  switch (st)   {
  case 0xfffd:  //тупик ('-'=-3)
         Chain.Pop(Proof.pr_NomR1); 
         Chain.Pop(st); 
         if ((int)st < 0) {  //тупик из одной строки
           Proof.pr_NomDom = -1;
           Proof.pr_NomR2  = -1;
           Proof.pr_NomRez = -1;
           NomRow.Push(Proof.pr_NomR1);  
           goto sw;
         }
         Proof.pr_NomDom = st;
         Chain.Pop(Proof.pr_NomR2);
         if (BuildNewStep(SDiz,MaskCol,&Proof,StepProof)) return ++nStep;
         if (++nStep > MaxStep) return -2;  
         NomRow.Push(Proof.pr_NomRez);  
         break;
  case 0xfffe:  //ветвление (':'=-2)
         Chain.Pop(Proof.pr_NomDom);
         Chain.Pop(NumbV);  Chain.Pop(st);
         NomRow.Pop(Proof.pr_NomR1); 
         NomRow.Pop(Proof.pr_NomR2);
         NumbV -=2;
         while (1)  {
           if (BuildNewStep(SDiz,MaskCol,&Proof,StepProof)) return ++nStep;
           if (++nStep > MaxStep) return -2;  
           if (NumbV)  {
             Proof.pr_NomR1 = Proof.pr_NomRez;
             NomRow.Pop(Proof.pr_NomR2);
             NumbV--;
           }
           else         {
             NomRow.Push(Proof.pr_NomRez);
             break;
           }  
         }
         break;
  default:  //продолжение обработки ветки
         Proof.pr_NomDom = st;
         Chain.Pop(Proof.pr_NomR2);  
         NomRow.Pop(Proof.pr_NomR1);
         if (BuildNewStep(SDiz,MaskCol,&Proof,StepProof)) return ++nStep;
         if (++nStep > MaxStep) return -2;
         NomRow.Push(Proof.pr_NomRez);  
  }       
 } //end while
 return nStep;
}

//---------------------------------------------------------------BuildNewStep
//  Построение очередного шага доказательства невыполнимости матрицы
//  Выход: 
//      TRUE - получен нулевой вектор при склейке строк
//-------------------------------------------------------------------
BOOL BuildNewStep(CBM& SDiz,CBV& MaskCol,struct pr *Proof,CWordArray& StepProof)
{ CBV Work(0,SDiz.GetCountC(),TRUE);
  CBV VectRez(0,SDiz.GetCountC(),TRUE);
  CBV Row1;
  CBV Row2;
  
  Work = ~MaskDom.GetRowBv(Proof-> pr_NomDom);
  Row1 = SDiz.GetRowBv(Proof-> pr_NomR1)&MaskCol;
  Row2 = SDiz.GetRowBv(Proof-> pr_NomR2)&MaskCol;
  VectRez = (Row1 & Work) | (Row2 & Work);
  Work = (MaskDom[Proof-> pr_NomDom] & Row1) & 
         (MaskDom[Proof-> pr_NomDom] & Row2);
  VectRez |= Work;
  Proof-> pr_NomRez = SDiz.Add(VectRez);
  StepProof.Add(Proof-> pr_NomR1);
  StepProof.Add(Proof-> pr_NomR2);
  StepProof.Add(Proof-> pr_NomDom);
  StepProof.Add(Proof-> pr_NomRez);
  if (VectRez.IsZero()) return TRUE;
  return FALSE;  
}

