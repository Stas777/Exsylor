#pragma once

#ifndef _COVERDOC
#define _COVERDOC

#include "BaseBool.h"
#include "QStack"
#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CoverDoc.h
/////////////////////////////////////////////////////////////////////////////
struct pr {
    int pr_NomR1;
    int pr_NomR2;
    int pr_NomDom;
    int pr_NomRez;
    };

class CStack : public QStack<int>
{
public:
  CStack();
// Operations
public:
// Accessing elements
  void Push(int x) {
      this->push(x);
  }

  BOOL Pop(int& x) {
      if (this->empty()) {
          return false;
      } else {
          x = this->pop();
          return true;
      }
  }
};

//----------------------------- Прототипы программ ----------------------COVER.CPP
bool Cover(CBM& Matr,CBV& MaskRez,CBV& MaskCol);
void CreatMaskDom();
bool RedRows (CBM& Matr, CBV& MaskRow, CBV& MaskCol);
void RedRowsDom(CBM& Matr, CBV& MaskRow, CBV& MaskCol);
bool RedRowsDom1(CBM& Matr, CBV& MaskRow, CBV& MaskCol);
void RedCols(CBM& tm, CBV& MaskRow, CBV& MaskCol);
void FindColsZero(CBM& tm, CBV& MaskRow, CBV& MaskCol);
int  ComputeNomDom(int nc);
bool OtherWay(CBM& MaskStepRow,CBM& MaskStepCol,CBV& MaskRow,CBV& MaskCol,
              CBV& MaskRez,vector<int>& StepColDom,int &step,int &nc);

//----------------------------- Прототипы программ ------------------DEDUCT.CPP
bool SimpleDiz(CBM& SDiz);
void AbsorbRows(CBM& SDiz,CBV& MaskRow);
void CheckOneDom(CBM& SDiz,CBV& MaskRow);
void DelRows(CBM& SDiz,CBV& MaskRow);
int  SearchSmDom(CBV& Vect1, CBV& Vect2,int nd, int& Fl);
void ComputeNewIndex(int& ind1, int& ind2, CBV& MaskRow);
bool PasteDom(CBV& Vect1, CBV& Vect2, CBV& VectRez, int nd);
bool AbsorbNewVect(CBM& SDiz, CBV& Vect, CBV& MaskRow);
int Recogn(CBM& Matr,CBM& RecMatr,CBV& RecVect,CBV& RecRez,int nd, int nv);

//----------------------------- Прототипы программ ------------------PROOF.CPP

int Proof(CBM& Matr,CBV& VectRec,vector<int>& StepProof);
bool BuildChainProof(CBM& SDiz,CBV& MaskCol,CStack& Chain);
int BuildStepsProof(CBM& SDiz, CBV& MaskCol,CStack& Chain, vector<int>& StepProof);
bool BuildNewStep(CBM& SDiz,CBV& MaskCol,struct pr *Proof,vector<int>& StepProof);

//----------------------------- Прототипы программ ------------------REDUCT.CPP
bool Reduction(CBM& Matr);
void RedDom1(CBM& Matr, CBV& MaskRow,CBV& MaskCol);
void CheckFollowRow(CBM& Matr);
void ChangeOneZero(CBM& Matr);
//----------------------------- Прототипы программ ------------------IND.CPP
//bool Induct(CBM& MatrCon,CBM& MatrDis);
void gen_diz(CBM& MatrCon, CBM& MatrDis, CBM& msk_une, char *kol_one);
int countbit(unsigned x);
void ChangeDom(CBV& Vect, int k, unsigned mask);
//----------------------------- Прототипы программ ------------------GEN_DAT.CPP
CBM GenDat(int exp, int nRowD, CBM& MatrK);
CBM GenKnow(int exp, int ver, int Rang, int nRowK);
CBV CrRandVect(int ver);
bool CreateReg(int Rang,CBV& Row,CBV& Reg);

#endif //_COVERDOC
