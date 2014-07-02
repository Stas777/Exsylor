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
extern CWordArray* DomVal;   //��������� �������
extern CWordArray* DomAdr;   //������ ������� � ������ (nDom+1 ���������)


//-------------------------------------------------------------BuildChainProof
//  ���������� �������������� �������������� �������
//  �����: 
//        -1 - ������� SDiz ���������
//        -2 - ����� ����� �������������� > MaxStep
//         n - ����� ����� ��������������
//         ��������� n ����� ������� Matr �������� ��������������
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
//  ���������� ������� ��� �������������� �������������� �������
//  �����: 
//        FALSE - ������� SDiz ���������
//        Chain - �������� ������� ���-��
//-------------------------------------------------------------
BOOL BuildChainProof(CBM& SDiz,CBV& VectRec,CStack& Chain)
{ int i,nRow,nd=0,nc,Fl;

 CBM tm(SDiz,FALSE);                // ���������� ����������������� �������
 CBV MaskCol(VectRec);
 nRow = SDiz.GetCountR();
 CBV MaskRow(1,nRow,TRUE);
 CBM StepMaskRow(nDoms,nRow);      //�-�� ����� ����� ��� ���������
 CBM StepMaskCol(nDoms,SDiz.GetCountC());    //�-�� ����� �������� ��� ���������
 CBV Work;
 CBV Mask;
 CWordArray Wdom;                   //������ ����� ������ � ������ MaskCol
 CWordArray Wrow;                   //������ ����� ����� � ������ MaskCol
 CWordArray NumbV;                  //������ ����� ��������� �� ������� ������ 
 CWordArray NumbCol;                //������ ������� �������� ��� ��������� 
 Wdom.SetSize(nRow);    Wrow.SetSize(nRow); 
 NumbV.SetSize(nDoms); NumbCol.SetSize(nDoms);
 for (i=0; i<nDoms; i++) { NumbV[i]=0; NumbCol[i]=-1; }
  
 RedCols(tm,MaskRow,MaskCol);            //�������� (���������� �������� ������ ������)
 FindColsZero(tm,MaskRow,MaskCol);       //���������� ������ ��������

//----------------------------------���������� ������� ����� �����a nd � ������ MaskCol
step1: Fl=0;
 Mask = MaskCol & MaskDom[nd];
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   Work = SDiz[i] & MaskCol;    Wrow[i]= Work.CountBit();
   if (Wrow[i] == 0) { Fl=1; break; }                   //�����
   Work = SDiz[i] & Mask;       Wdom[i]= Work.CountBit();
 }
 if (Fl) { 
   Chain.Push(i);  Chain.Push(-3);  //������ � ���� 1)����� ������, 2)'-'(-3)
   if (nd) goto next;
   goto fin;
 }
 
//-----------------------------------------------------------����� ������ ��� ��������
 Fl=0; 
 for (i=MaskRow.LeftOne(); i>=0; i=MaskRow.LeftOne(i)) {
   if (Wdom[i] > 1) continue;
   if (Wrow[i] == 1) { Fl=1; break; }
 }
 if (Fl) { 
   if (Wdom[i] == 0) {
     nc = (SDiz[i] & MaskCol).LeftOne();
     nd = ComputeNomDom(nc);         //���-��� N ������ �� N ������� � ������
   }  
   Chain.Push(i); Chain.Push(nd);  //������ � ���� 1)����� ������, 2)����� ������
   Work = SDiz[i] & MaskCol & MaskDom[nd];
   nc = Work.LeftOne();
 }
 else     {
   Work = MaskCol & MaskDom[nd];
   NumbV[nd] = Work.CountBit();             //����� ���������
   Chain.Push(-1);  Chain.Push(NumbV[nd]);  //������ � ���� 1)'+', 2)����� ���������
   Chain.Push(nd);  Chain.Push(-2);         //������ � ���� 3)����� ������, 4)':'
   nc = Work.LeftOne();
   StepMaskRow.SetRow(nd, MaskRow);
   StepMaskCol.SetRow(nd, MaskCol);
   NumbCol[nd] = nc;   
 }
//------------------------------------------------------������������� MaskRow, MaskCol
step2: 
 MaskCol &= ~MaskDom.GetRowBv(nd);  MaskRow &= ~tm.GetRowBv(nc);
 if (MaskRow.IsZero()) return FALSE;
 if ((i=MaskCol.LeftOne()) >=0) {
   nd = ComputeNomDom(i);         //���-��� N ������ �� N ������� � ������
   goto step1;
 }  
 i = MaskRow.LeftOne();
 Chain.Push(i);  Chain.Push(-3);  //������ � ���� 1)����� ������, 2)'-'(-3)

//------------------------------------------------����������� ���������� ������ ������
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
//  ���������� ����� �������������� �������������� �������
//  ����: 
//      SDiz  - �������� �������
//      Chain - ����, ���������� ������� ��� ���������� ���-��
//  �����: 
//      nStep - ����� ����� ��������������,
//              ��� -2 ��� nStep > MaxStep
//      SDiz  - �������� ������� + nStep ����� ��������������
//  StepProof - ������ (nStep � 4): 1)NomR1, 2)NomR2, 3)NomDom, 4)NomRez
//----------------------------------------------------------------------
int BuildStepsProof(CBM& SDiz, CBV& MaskCol,CStack& Chain, CWordArray& StepProof)
{ int nStep=0;
  WORD NumbV,st;
  CStack NomRow;             //������� ���� ������� ����� ��� ���������� ���-�� 
  struct pr Proof;
  
 while (Chain.Pop(st))   { //���� Chain �� ����
sw: 
  switch (st)   {
  case 0xfffd:  //����� ('-'=-3)
         Chain.Pop(Proof.pr_NomR1); 
         Chain.Pop(st); 
         if ((int)st < 0) {  //����� �� ����� ������
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
  case 0xfffe:  //��������� (':'=-2)
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
  default:  //����������� ��������� �����
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
//  ���������� ���������� ���� �������������� �������������� �������
//  �����: 
//      TRUE - ������� ������� ������ ��� ������� �����
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

