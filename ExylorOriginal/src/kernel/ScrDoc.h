// scrdoc.h : interface of the CScriptDoc class
// 28.05.97 22:24
/////////////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------------
class CSample : public CObject
{
public:
    CSample();
    DECLARE_SERIAL(CSample)
// Attributes
    CByteArray m_Values;
// Operations
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

//------------------------------------------------------------------------
class CSBlock : public CObArray
{
public:
  CSBlock();
  DECLARE_DYNCREATE(CSBlock)

// Attributes
//    int       m_nElements;     // Number of regularities/samples
// Замена на GetSize
    CString   m_sTitle;        // Name of block  - Key for Map

    // Operations
public:
// Accessing elements
  CSample* GetAt(int nIndex) const;
  void SetAt(int nIndex, CSample* newElement);
  int Add(CSample* newElement);
  void RemoveAll();
  virtual void Serialize(CArchive& ar);   // overridden for document i/o
};


//------------------------------------------------------------------------
//class CBlockScript : public CObject
//{
//public:
//    CBlockScript();
//    DECLARE_SERIAL(CBlockScript)

// Operations
//public:
//    virtual void Serialize(CArchive& ar);   // overridden for document i/o
//};

//------------------------------------------------------------------------
class CBlockMap : public CMapStringToOb
{
public:
  CBlockMap();
  DECLARE_DYNCREATE(CBlockMap)
// Operations
public:
  void GetNextAssoc(POSITION& rNextPosition, CString& rKey, CSBlock*& rValue);
  BOOL Lookup(const char* key, CSBlock*& rValue);
  void SetAt(const char* key, CSBlock* newValue);
  void RemoveAll();
  CString GetFirstKey();
  int GetElemForActive(CString& rKey);
  void Serialize(CArchive& ar);
};

//------------------------------------------------------------------------
class CkAttr : public CObject
{
public:
    CkAttr();
    DECLARE_SERIAL(CkAttr)
// Attributes
    CString       m_sTitle;     // Name of attribute
    CStringArray  m_ValNames;   // Names of attribute values
    CBV  m_DFlag;               // Attribute values flags
    CBV  m_KifFlag;             // Attribute values flags
    CBV  m_KthenFlag;           // Attribute values flags
// Operations
public:
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
};

//------------------------------------------------------------------------
class CkAttrArray : public CObArray
{
public:
  CkAttrArray();
  DECLARE_DYNCREATE(CkAttrArray)
// Operations
public:
// Accessing elements
  CkAttr* GetAt(int nIndex) const;
  void SetAt(int nIndex, CkAttr* newElement);
  int Add(CkAttr* newElement);
  void RemoveAll();
};

//------------------------------------------------------------------------
//------------------------------------------------------------------------
class CScriptDoc : public CDocument
{
protected: // create from serialization only
   CScriptDoc();
   DECLARE_DYNCREATE(CScriptDoc)

// Attributes
public:
// Know---------------------
   BOOL ModeInput;               // 0 - If, else Then
   CSBlock m_pReguls;
   CStringArray m_sRegulWord;     // For word viewer
   int m_sRegulWordCount;         // Rows number for word viewer
   int m_ActReg;
   int ChangeReg;



// Data---------------------
   CSBlock m_pSamples;
   CStringArray m_sWord;  // For word viewer
   int m_sWordCount;      // Rows number for word viewer
   int m_ActSmp;
   int ChangeOb;

// Model---------------------
   CWordArray m_TreeRow;        // HIBYTE- number of attribute;LOBYTE - number of his value
   int m_ActDRow;
   int m_ActKRow;
   int       m_nAttributes;    // Number of attributes
   int       m_nValues;        // Number of values generally
   CBlockMap m_KBMap;          // Map of knowledge script blocks
   CBlockMap m_DBMap;          // Map of data script blocks
   CString   m_ActKB;          // Name of active knowledge script blok
   CString   m_ActDB;          // Name of active data script blok

   CkAttrArray m_pAttrObj;     // attributes (for active model)

// Others---------------------
   int m_nDom;            //number of domens (attributes)
   CWordArray m_DomVal;   //values in domens
   CWordArray m_DomAdr;   //address of attribute domens in string(nDom+1 elements)
   CBM m_Matr;            //matrix
   CBV m_Vect;            //vector
   CBV m_RowMask;         //vector (anti)scale for contradict rows
   CBV m_Answer ;         //answer of recognition
   BOOL CheckObject;      //recognition is done
   int m_nRecAtr;         // number of attribute for recognition
   int m_nRecVal;         // number of value for recognition
   BOOL m_nRecResult;     // True - is valid, False - is not valid -> proof
   CString m_sStage;
   CWordArray m_StepProof;
   int m_NumStep;
   int m_ActStep;
   CBM m_RecMatr;         // matrix of valid sets for recognition
   CBM m_MatrAndObj;      // matrix of valid sets for recognition
   CStringArray m_sExplan;
   CStringArray m_sExplanStep;

// Inductive---------------------
   int Num_Con;
   int Rank;
   int Numb;
   double Prob;
   int FactRank;
   int FactNum;
   double FactProb;
   HWND hTable;
   
//  Implementation
public:

   BOOL Induct(CBM& MatrCon,CBM& MatrDis);
   int  ind_bound(double *bounds,int n );
   int Mat(int n,double *bound,int kol,double *pn,double *qn, double * New);
   
//-----------------------include EXS_OLD.CPP----------------------
   CString Beg_z(int n,int atr,int val,CBV& con);
   void FormCon(CString& W);
   void FormObj(CString& W);
   void OneAttrib(CString& W,CBV& bv,CkAttr* pAttr, int j);
   void if_diz (CBV& vect,CString& form);
   void Diz_form (CBV& msk, int atr, int val, CString s,CString& form);
   CString if_4(CBM matr, int step);
   void PutMatrixProof();
   void get_vct(CString& form,CBV& vct0,int pr);
   void PutFormulaProof();
//-----------------------include LINKUSER.CPP----------------------
   void RecognObject();
   void PrepareRec(int atr, int val);
   BOOL DirectContra(CBM& Matr,CBV& RecVect);
   void GetAim_ViewProof();
   void PrepareProof(int atr, int val);
   void SplitRows();
   void GetStep(int atr, int val);
   void StringToArray(CStringArray& Arr,CString W);
   void ToVect(CBV& Vect);
   void FromVect(CBV& Vect);
   BOOL ToMatrCon(CBM& Matr);
   BOOL ToMatr(CBM& Matr);
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
     void InitTree(BOOL Act,BYTE Val); // 0 - D, 1 - K
     BOOL WriteReadSmp(CString& FileName,BOOL Op);
     void CancelSampleInput(BOOL Fl);         // Cancel mode NEW_SAMPLE
     void DBClose(BOOL Fl);
     BOOL DBSave();
     void DBDelete();

     void KBClose(BOOL Fl);
     BOOL KBSave();
     void KBDelete();
     BOOL WriteReadReg(CString& FileName,BOOL Op);
     void CancelRegInput(BOOL Fl);         // Cancel mode NEW_REGUL

//-----------------------include SCRINIT.CPP----------------------
    void ChangeSelectionNextRowNo(BOOL bNext,int& Act);
    void ChangeSelectionToRowNo(int nNo,int& Act);
    void ChangeSelectionNextSmpNo(BOOL bNext);
    void ChangeSelectionToSmpNo(int nNo);
    void ChangeSelectionNextRegNo(BOOL bNext);
    void ChangeSelectionToRegNo(int nNo);
    void NextView(CRuntimeClass* pViewClass);

//-----------------------include ScrDocExpImp.cpp-----------------
    void ModelExport();  // Импорт прямо с диалога создания модели!
    void DbExport();
    void DbImport();
    void KbExport();
    void KbImport();

protected:
    virtual ~CScriptDoc();
       void DeleteContents();
       void SetModifiedFlag();
    virtual BOOL OnNewDocument();
    virtual BOOL OnOpenDocument(const char* pszPathName );
    virtual BOOL OnSaveDocument(const char* pszPathName);
    virtual void OnCloseDocument();
    virtual void Serialize(CArchive& ar);   // overridden for document i/o
#ifdef _DEBUG
    virtual void AssertValid() const;
    virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
   //{{AFX_MSG(CScriptDoc)
    afx_msg void OnUpdateScriptNew(CCmdUI* pCmdUI);
    afx_msg void OnModelEdit();
    afx_msg void OnDBNew();
    afx_msg void OnUpdateDBNew(CCmdUI* pCmdUI);
    afx_msg void OnDBOpen();
    afx_msg void OnUpdateDBOpen(CCmdUI* pCmdUI);
    afx_msg void OnDBSave();
    afx_msg void OnUpdateDBSave(CCmdUI* pCmdUI);
    afx_msg void OnDBClose();
    afx_msg void OnDBEdit();
    afx_msg void OnDBDelete();
    afx_msg void OnKBNew();
    afx_msg void OnUpdateKBNew(CCmdUI* pCmdUI);
    afx_msg void OnKBOpen();
    afx_msg void OnKBSave();
    afx_msg void OnUpdateKBSave(CCmdUI* pCmdUI);
    afx_msg void OnKBClose();
    afx_msg void OnKBEdit();
    afx_msg void OnKBDelete();
    afx_msg void OnDataAddSmp();
    afx_msg void OnUpdateDataAddSmp(CCmdUI* pCmdUI);
    afx_msg void OnDataClearSmp();
    afx_msg void OnDataDelSmp();
    afx_msg void OnDataInsertSmp();
    afx_msg void OnDataReadSmp();
    afx_msg void OnDataWriteSmp();
    afx_msg void OnDataInd();
    afx_msg void OnUpdateDataInd(CCmdUI* pCmdUI);
    afx_msg void OnRegAdd();
    afx_msg void OnUpdateRegAdd(CCmdUI* pCmdUI);
    afx_msg void OnRegClear();
    afx_msg void OnRegDel();
    afx_msg void OnRegInsert();
    afx_msg void OnRegRead();
    afx_msg void OnRegWrite();
    afx_msg void OnRegNext();
    afx_msg void OnRecognFull();
    afx_msg void OnRecognAtr();
    afx_msg void OnRecognVal();
    afx_msg void OnKnowReduct();
    afx_msg void OnUpdateKnowReduct(CCmdUI* pCmdUI);
    afx_msg void OnRecognObject();
    afx_msg void OnRecognProof();
    afx_msg void OnUpdateRecognProof(CCmdUI* pCmdUI);
    afx_msg void OnUpdateRecogn(CCmdUI* pCmdUI);
    afx_msg void OnStepFirst();
    afx_msg void OnStepLast();
    afx_msg void OnStepNext();
    afx_msg void OnUpdateStepNext(CCmdUI* pCmdUI);
    afx_msg void OnStepPrev();
    afx_msg void OnUpdateStepPrev(CCmdUI* pCmdUI);
    afx_msg void OnProofMatrix();
    afx_msg void OnProofFormula();
    afx_msg void OnUpdateModel(CCmdUI* pCmdUI);
    afx_msg void OnUpdateKBEdit(CCmdUI* pCmdUI);
    afx_msg void OnUpdateKnowOpen(CCmdUI* pCmdUI);
    afx_msg void OnDataGen();
    afx_msg void OnKnowGen();
	afx_msg void OnSystem();
	afx_msg void OnModelExport();
	afx_msg void OnDbExport();
	afx_msg void OnDbImport();
	afx_msg void OnKbExport();
	afx_msg void OnKbImport();
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
