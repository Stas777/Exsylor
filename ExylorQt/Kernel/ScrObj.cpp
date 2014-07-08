// scrobj.cpp : implementation of the CCoverDoc class
// 17.05.2007 -------------------------------------
//
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <math.h>
#include "CoverDoc.h"
#include "ScrDoc.h"
#include "Archive.h"
#include <QString>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

int nDoms;
CBM MaskDom;
QVector<int>* DomVal;   //значность доменов
QVector<int>* DomAdr;   //адреса доменов в строке (nDom+1 элементов)

extern QVector<QString> Ins_txt;
//void get_tx (int numb_txt,string& Txt);


// Class realization for Script Document Objects:
/////////////////////////////////////////////////////////////////////////////
// scrobj.cpp : implementation of the CScriptDoc  Objects classes
// 06.05.97 23:51
/////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////// CSample

//------------------------------------------------------------- Constructor
CSample::CSample() { } // This empty constructor
//------------------------------------------------------------- Serialize
void CSample::Serialize(CArch& ar) {
    for (uint i = 0; i < m_Values.size(); ++i) {
        if (ar.IsStoring()){   // storing code here
            ar<<m_Values[i];
            //ar<<sampleArr;
        }
        else{                  // loading code here
            ar>>m_Values[i];
            //ar>>sampleArr;
        }
    }
}
/////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////// CSampleBlock

CSBlock::CSBlock() { }
//---------------------------------------------------------------
CSample* CSBlock::GetAt(int nIndex)  const
{ return (CSample*) m_sampleArr.at(nIndex); }
//---------------------------------------------------------------
void CSBlock::SetAt(int nIndex, CSample* newElement){
    m_sampleArr[nIndex] = newElement;
}
//---------------------------------------------------------------
int CSBlock::Add(CSample* newElement){
    m_sampleArr.push_back(newElement);
    return m_sampleArr.size() - 1;
}
//---------------------------------------------------------------
void CSBlock::RemoveAll()
{
    m_sampleArr.clear();
}
//---------------------------------------------------------------
void CSBlock::Serialize(CArch& ar)
{
    if (ar.IsStoring()){   // storing code here
        ar<<m_sTitle;
        //ar<<sampleArr;
    }
    else{                  // loading code here
        ar>>m_sTitle;
        //ar>>sampleArr;
    }
}

/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CBlockScriptMap

//--------------------------------------------------------------- Constructor
CBlockMap::CBlockMap() { }
//---------------------------------------------------------------
void CBlockMap::RemoveAll()
{
    foreach(CSBlock* pBlock, m_blockMap) {
        pBlock->m_sTitle.clear();
        pBlock->RemoveAll();
        delete pBlock;
  }
  m_blockMap.clear();
}




void CBlockMap::Serialize(CArch& ar)
{
    QString key;
    if (ar.IsStoring()) {
            ar<<m_blockMap.size();
            foreach(CSBlock* pBlock, m_blockMap)  {
                pBlock->Serialize(ar);
            }
    } else {
        CSBlock *pBlock;
        DWORD nNewCount;
        ar>>nNewCount;
        while (nNewCount--) {
			pBlock = new CSBlock;
            pBlock->Serialize(ar);
            if (!pBlock->m_sTitle.isEmpty()) {
                SetAt(&(pBlock->m_sTitle), pBlock);
            }
		}
	}
}

//---------------------------------------------------------------
BOOL CBlockMap::Lookup(const QString* key, CSBlock*& rValue) {
    rValue = m_blockMap[*key];
    if (rValue == NULL) {
        return false;
    } else {
        return true;
    }
}
//---------------------------------------------------------------
void CBlockMap::SetAt(const QString* key, CSBlock* newValue) {
    m_blockMap.insert(*key, newValue);
}
/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CkAttr

//------------------------------------------------------------- Constructor
CkAttr::CkAttr() { } // This is empty constructor
//------------------------------------------------------------- Serialize
void CkAttr::Serialize(CArch& ar) {
    if (ar.IsStoring()) {
        ar<<m_sTitle;
    } // storing code here
    else {
        ar>>m_sTitle;
    } // loading code here

    foreach(QString qstr, m_ValNames) {
        if (ar.IsStoring()) {
            ar<<qstr;
        } // storing code here
        else {
            ar>>qstr;
        } // loading code here
    }
}

/////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////// CkAttrArray

CkAttrArray::CkAttrArray() { }
//---------------------------------------------------------------
CkAttr* CkAttrArray::GetAt(int nIndex)  const {
    return m_attrArr.at(nIndex);
}
//---------------------------------------------------------------
void CkAttrArray::SetAt(int nIndex, CkAttr* newElement) {
    m_attrArr[nIndex] = newElement;
}
//---------------------------------------------------------------
int CkAttrArray::Add(CkAttr* newElement) {
    m_attrArr.push_back(newElement);
    return m_attrArr.size() - 1;
}
//---------------------------------------------------------------
void CkAttrArray::RemoveAll() {
    int i;
    foreach(CkAttr* pAttr, m_attrArr) {
        delete(pAttr);
    }
    m_attrArr.clear();
}

int CkAttrArray::GetSize() {
    return m_attrArr.size();
}

/////////////////////////////////////////////////////////////////////////////


