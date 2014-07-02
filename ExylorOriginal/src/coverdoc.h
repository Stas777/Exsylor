#ifndef _COVERDOC
#define _COVERDOC

/////////////////////////////////////////////////////////////////////////////
// CoverDoc.h
/////////////////////////////////////////////////////////////////////////////
struct pr {
    WORD pr_NomR1;
    WORD pr_NomR2;
    WORD pr_NomDom;
    WORD pr_NomRez;
    };


//------------------------------------------------------------------------
class CStack : public CWordArray 
{
public:
  CStack(); 
  DECLARE_DYNCREATE(CStack)
// Operations
public:
// Accessing elements
  void Push(WORD El);
  BOOL Pop(WORD& El);
};


//----------------------------- Прототипы программ ----------------------COVER.CPP
BOOL Cover(CBM& Matr,CBV& MaskRez,CBV& MaskCol);
void CreatMaskDom();
BOOL RedRows (CBM& Matr, CBV& MaskRow, CBV& MaskCol);
void RedRowsDom(CBM& Matr, CBV& MaskRow, CBV& MaskCol);
BOOL RedRowsDom1(CBM& Matr, CBV& MaskRow, CBV& MaskCol);
void RedCols(CBM& tm, CBV& MaskRow, CBV& MaskCol);
void FindColsZero(CBM& tm, CBV& MaskRow, CBV& MaskCol);
int  ComputeNomDom(int nc);
BOOL OtherWay(CBM& MaskStepRow,CBM& MaskStepCol,CBV& MaskRow,CBV& MaskCol,
              CBV& MaskRez,CWordArray& StepColDom,int &step,int &nc);

//----------------------------- Прототипы программ ------------------DEDUCT.CPP
BOOL SimpleDiz(CBM& SDiz);
void AbsorbRows(CBM& SDiz,CBV& MaskRow);
void CheckOneDom(CBM& SDiz,CBV& MaskRow);
void DelRows(CBM& SDiz,CBV& MaskRow);
int  SearchSmDom(CBV& Vect1, CBV& Vect2,int nd, int& Fl);
void ComputeNewIndex(int& ind1, int& ind2, CBV& MaskRow);
BOOL PasteDom(CBV& Vect1, CBV& Vect2, CBV& VectRez, int nd);
BOOL AbsorbNewVect(CBM& SDiz, CBV& Vect, CBV& MaskRow);
int Recogn(CBM& Matr,CBM& RecMatr,CBV& RecVect,CBV& RecRez,int nd, int nv);

//----------------------------- Прототипы программ ------------------PROOF.CPP

int Proof(CBM& Matr,CBV& VectRec,CWordArray& StepProof);
BOOL BuildChainProof(CBM& SDiz,CBV& MaskCol,CStack& Chain);
int BuildStepsProof(CBM& SDiz, CBV& MaskCol,CStack& Chain, CWordArray& StepProof);
BOOL BuildNewStep(CBM& SDiz,CBV& MaskCol,struct pr *Proof,CWordArray& StepProof);

//----------------------------- Прототипы программ ------------------REDUCT.CPP
BOOL Reduction(CBM& Matr);
void RedDom1(CBM& Matr, CBV& MaskRow,CBV& MaskCol);
void CheckFollowRow(CBM& Matr);
void ChangeOneZero(CBM& Matr);
//----------------------------- Прототипы программ ------------------IND.CPP
//BOOL Induct(CBM& MatrCon,CBM& MatrDis);
void gen_diz(CBM& MatrCon, CBM& MatrDis, CBM& msk_une, char *kol_one);
int countbit(unsigned x);
void ChangeDom(CBV& Vect, int k, unsigned mask);
//----------------------------- Прототипы программ ------------------GEN_DAT.CPP
CBM GenDat(int exp, int nRowD, CBM& MatrK);
CBM GenKnow(int exp, int ver, int Rang, int nRowK);
CBV CrRandVect(int ver);
BOOL CreateReg(int Rang,CBV& Row,CBV& Reg);

#endif //_COVERDOC