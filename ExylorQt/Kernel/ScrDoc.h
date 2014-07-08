// scrdoc.h : interface of the CScriptDoc class
// 28.05.97 22:24
/////////////////////////////////////////////////////////////////////////////
#pragma once

#include <QString>
#include <QVector>
#include <QMap>
#include "Archive.h"
#include "BaseBool.h"


//------------------------------------------------------------------------
class CSample
{
public:
    CSample();
// Attributes
    QVector<char> m_Values;
// Operations
    virtual void Serialize(CArch& ar);   // overridden for document i/o
};

//------------------------------------------------------------------------
class CSBlock
{
public:
  CSBlock();
  QVector<CSample*> m_sampleArr;

// Attributes
//    int       m_nElements;     // Number of regularities/samples
// Замена на GetSize
    QString   m_sTitle;        // Name of block  - Key for Map


    // Operations
public:
// Accessing elements
  CSample* GetAt(int nIndex) const;
  void SetAt(int nIndex, CSample* newElement);
  int Add(CSample* newElement);
  void RemoveAll();
  virtual void Serialize(CArch& ar);   // overridden for document i/o
};


//------------------------------------------------------------------------
//class CBlockScript : public CObject
//{
//public:
//    CBlockScript();
//    DECLARE_SERIAL(CBlockScript)

// Operations
//public:
//    virtual void Serialize(CArch& ar);   // overridden for document i/o
//};

//------------------------------------------------------------------------
class CBlockMap
{
public:
  CBlockMap();
  QMap<QString, CSBlock*> m_blockMap;
// Operations
public:
  bool Lookup(const QString* key, CSBlock*& rValue);
  void SetAt(const QString *key, CSBlock* newValue);
  void RemoveAll();
  void Serialize(CArch& ar);
};

//------------------------------------------------------------------------
class CkAttr {
public:
    CkAttr();
// Attributes
    QString       m_sTitle;     // Name of attribute
    QVector<QString>  m_ValNames;   // Names of attribute values
    CBV  m_DFlag;               // Attribute values flags
    CBV  m_KifFlag;             // Attribute values flags
    CBV  m_KthenFlag;           // Attribute values flags
// Operations
public:
    virtual void Serialize(CArch& ar);   // overridden for document i/o
};

//------------------------------------------------------------------------
class CkAttrArray
{
public:
  CkAttrArray();
  QVector<CkAttr*> m_attrArr;
// Operations
public:
// Accessing elements
  CkAttr* GetAt(int nIndex) const;
  void SetAt(int nIndex, CkAttr* newElement);
  int Add(CkAttr* newElement);
  int GetSize();
  void RemoveAll();
};

//------------------------------------------------------------------------
//------------------------------------------------------------------------
class CScriptDoc {
protected: // create from serialization only
   CScriptDoc();

// Attributes
public:
// Know---------------------
    bool ModeInput;                      // 0 - If, else Then
    CSBlock m_pReguls;
    QVector<QString> m_sRegulWord;     // For word viewer
    int m_sRegulWordCount;         // Rows number for word viewer
    int m_ActReg;
    int ChangeReg;



// Data---------------------
    CSBlock m_pSamples;
    QVector<QString> m_sWord;  // For word viewer
    int m_sWordCount;      // Rows number for word viewer
    int m_ActSmp;
    int ChangeOb;

// Model---------------------
    QVector<int> m_TreeRow;        // HIBYTE- number of attribute;LOBYTE - number of his value
    int m_ActDRow;
    int m_ActKRow;
    int       m_nAttributes;    // Number of attributes
    int       m_nValues;        // Number of values generally
    CBlockMap m_KBMap;          // Map of knowledge script blocks
    CBlockMap m_DBMap;          // Map of data script blocks
    QString   m_ActKB;          // Name of active knowledge script blok
    QString   m_ActDB;          // Name of active data script blok

    CkAttrArray m_pAttrObj;     // attributes (for active model)

// Others---------------------
    int m_nDom;            //number of domens (attributes)
    QVector<int> m_DomVal;   //values in domens
    QVector<int> m_DomAdr;   //address of attribute domens in QString(nDom+1 elements)
    CBM m_Matr;            //matrix
    CBV m_Vect;            //vector
    CBV m_RowMask;         //vector (anti)scale for contradict rows
    CBV m_Answer ;         //answer of recognition
    bool CheckObject;      //recognition is done
    int m_nRecAtr;         // number of attribute for recognition
    int m_nRecVal;         // number of value for recognition
    bool m_nRecResult;     // True - is valid, False - is not valid -> proof
    QString m_sStage;
    QVector<int> m_StepProof;
    int m_NumStep;
    int m_ActStep;
    CBM m_RecMatr;         // matrix of valid sets for recognition
    CBM m_MatrAndObj;      // matrix of valid sets for recognition
    QVector<QString> m_sExplan;
    QVector<QString> m_sExplanStep;

// Inductive---------------------
    int Num_Con;
    int Rank;
    int Numb;
    double Prob;
    int FactRank;
    int FactNum;
    double FactProb;
    //HWND hTable;
   
//  Implementation
public:

    bool Induct(CBM& MatrCon,CBM& MatrDis);
    int  ind_bound(double *bounds,int n );
    int Mat(int n,double *bound,int kol,double *pn,double *qn, double * New);
   
//-----------------------include EXS_OLD.CPP----------------------
    QString Beg_z(int n,int atr,int val,CBV& con);
    void FormCon(QString& W);
    void FormObj(QString& W);
    void OneAttrib(QString& W,CBV& bv,CkAttr* pAttr, int j);
    void if_diz (CBV& vect,QString& form);
    void Diz_form (CBV& msk, int atr, int val, QString s,QString& form);
    QString if_4(CBM matr, int step);
    void PutMatrixProof();
    void get_vct(QString& form,CBV& vct0,int pr);
    void PutFormulaProof();
//-----------------------include LINKUSER.CPP----------------------
    void RecognObject();
    void PrepareRec(int atr, int val);
    bool DirectContra(CBM& Matr,CBV& RecVect);
    void GetAim_ViewProof();
    void PrepareProof(int atr, int val);
    void SplitRows();
    void GetStep(int atr, int val);
    void StringToArray(QVector<QString>& Arr,QString W);
    void ToVect(CBV& Vect);
    void FromVect(CBV& Vect);
    bool ToMatrCon(CBM& Matr);
    bool ToMatr(CBM& Matr);
    void FromMatr(CBM& Matr);
    void FromMatrDB(CBM& Matr);

//-----------------------include SCRDOCSM.CPP----------------------
    void ForDefSmp();                              // For WORDVIEW
    void FormOneSmp(CSample* pSmp);
    void EndOneSmp();
    void AddOneSmp();
    void WriteOneSmp();
    void InsertOneSmp();
    void GetOneSmp(int nR);
    void DelCurrentSmp();
    void ClearSmp();
    void ReadCurrentSmp();
//-----------------------include SCRDOCRG.CPP----------------------
    void ForDefReg();                           // For WORDREGVIEW
    void FormOneReg(CSample* pReg);
    void EndOneReg();
    void AddOneReg();
    void GetOneReg(int nR);
    void WriteOneReg();
    void InsertOneReg();
    void DelCurrentReg();
    void ClearReg();
    void ReadCurrentReg();
    void NextPart();
//-----------------------include SCRDOCMD.CPP----------------------
    void InitModel();
    int NewModel();
    void InitTree(bool Act,BYTE Val); // 0 - D, 1 - K
    bool WriteReadSmp(QString& FileName,bool Op);
    void CancelSampleInput(bool Fl);         // Cancel mode NEW_SAMPLE
    void DBClose(bool Fl);
    bool DBSave();
    void DBDelete();

    void KBClose(bool Fl);
    bool KBSave();
    void KBDelete();
    bool WriteReadReg(QString& FileName,bool Op);
    void CancelRegInput(bool Fl);         // Cancel mode NEW_REGUL

//-----------------------include SCRINIT.CPP----------------------
    void ChangeSelectionNextRowNo(bool bNext,int& Act);
    void ChangeSelectionToRowNo(int nNo,int& Act);
    void ChangeSelectionNextSmpNo(bool bNext);
    void ChangeSelectionToSmpNo(int nNo);
    void ChangeSelectionNextRegNo(bool bNext);
    void ChangeSelectionToRegNo(int nNo);
    //void NextView(CRuntimeClass* pViewClass);

//-----------------------include ScrDocExpImp.cpp-----------------
    void ModelExport();  // Импорт прямо из диалога создания модели!
    void DbExport();
    void DbImport();
    void KbExport();
    void KbImport();

protected:
    virtual ~CScriptDoc();
    void DeleteContents();
    void SetModifiedFlag();
    virtual bool OnNewDocument();
    virtual bool OnOpenDocument(const char* pszPathName );
    virtual bool OnSaveDocument(const char* pszPathName);
    virtual void OnCloseDocument();
    virtual void Serialize(CArch& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message Map functions
protected:
   //{{AFX_MSG(CScriptDoc)
       /*
     void OnUpdateScriptNew(CCmdUI* pCmdUI);
     void OnModelEdit();
     void OnDBNew();
     void OnUpdateDBNew(CCmdUI* pCmdUI);
     void OnDBOpen();
     void OnUpdateDBOpen(CCmdUI* pCmdUI);
     void OnDBSave();
     void OnUpdateDBSave(CCmdUI* pCmdUI);
     void OnDBClose();
     void OnDBEdit();
     void OnDBDelete();
     void OnKBNew();
     void OnUpdateKBNew(CCmdUI* pCmdUI);
     void OnKBOpen();
     void OnKBSave();
     void OnUpdateKBSave(CCmdUI* pCmdUI);
     void OnKBClose();
     void OnKBEdit();
     void OnKBDelete();
     void OnDataAddSmp();
     void OnUpdateDataAddSmp(CCmdUI* pCmdUI);
     void OnDataClearSmp();
     void OnDataDelSmp();
     void OnDataInsertSmp();
     void OnDataReadSmp();
     void OnDataWriteSmp();
     void OnDataInd();
     void OnUpdateDataInd(CCmdUI* pCmdUI);
     void OnRegAdd();
     void OnUpdateRegAdd(CCmdUI* pCmdUI);
     void OnRegClear();
     void OnRegDel();
     void OnRegInsert();
     void OnRegRead();
     void OnRegWrite();
     void OnRegNext();
     void OnRecognFull();
     void OnRecognAtr();
     void OnRecognVal();
     void OnKnowReduct();
     void OnUpdateKnowReduct(CCmdUI* pCmdUI);
     void OnRecognObject();
     void OnRecognProof();
     void OnUpdateRecognProof(CCmdUI* pCmdUI);
     void OnUpdateRecogn(CCmdUI* pCmdUI);
     void OnStepFirst();
     void OnStepLast();
     void OnStepNext();
     void OnUpdateStepNext(CCmdUI* pCmdUI);
     void OnStepPrev();
     void OnUpdateStepPrev(CCmdUI* pCmdUI);
     void OnProofMatrix();
     void OnProofFormula();
     void OnUpdateModel(CCmdUI* pCmdUI);
     void OnUpdateKBEdit(CCmdUI* pCmdUI);
     void OnUpdateKnowOpen(CCmdUI* pCmdUI);
     void OnDataGen();
     void OnKnowGen();
     void OnSystem();
     void OnModelExport();
     void OnDbExport();
     void OnDbImport();
     void OnKbExport();
     void OnKbImport();*/
    //}}AFX_MSG
};
/////////////////////////////////////////////////////////////////////////////
