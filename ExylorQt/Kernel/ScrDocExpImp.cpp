// scrdocExpImp.cpp : implementation of the CExsDoc class
// 30.05.2007 -------------------------------------
/*
#include <ctype.h>



#include "ScrDoc.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
void GetFileLine(FILE *f, int& len, QString& s)
{
  char b[2];
  s="";
  while (len>0) {
     fscanf(f,"%c",&b[1]); len--;
      if (b[0]=='\r') { fscanf(f,"%c",&b[1]); len--; return; }  // Пропускаем еще \n
    else s+=b[0];
  }
}

/////////////////////////////////////////////////////////////////////////////
// CScriptDoc


/////////////////////////////////////////////////////////////////////////////
// CScriptDoc commands  /////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// ***     ***   ****    ****     ******  ****
//  ***   ***   **  **   **  **   ******   **
//  **** ****  **    **  **   **  **       **
//  ** *** **  **    **  **   **  *****    **
//  **  *  **  **    **  **   **  **       **   **
//  **     **   **  **   **  **   ******   *******
// ****   ****   ****    ****     ******  ********

//------------------------------------------------------------------ModelExport
/*void CScriptDoc::ModelExport()
{
  QString W,W0;
  int i, j;
  CkAttr* pAttr;

	W = "Model script (*.mod)|*.mod|All files (*.*)|*.*||" ;
  W0 = "mod";
  QString FileName, FileExt;
  CFileDialog dlg(FALSE, W0, "Model",
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );
  FileExt = dlg.GetFileExt( ); 
  if (FileExt.IsEmpty()) FileName += "." + W0;

  TRY
  {
    CFile f(FileName,CFile::modeWrite|CFile::modeCreate);

    for (i=0; i <m_pAttrObj.GetSize(); i++) {
      pAttr = m_pAttrObj.GetAt(i); 
      f.Write(pAttr->m_sTitle,pAttr->m_sTitle.GetLength());
      f.Write("\r\n",2);
      for (j=0; j <pAttr->m_ValNames.GetSize(); j++) {
        f.Write(" ",1);
        f.Write(pAttr->m_ValNames[j], pAttr->m_ValNames[j].GetLength());
        f.Write("\r\n",2);
      }
    }
  }
  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the writing file " + FileName);
  }
  END_CATCH
}
*/

/////////////////////////////////////////////////////////////////////////////////
//   ****       ****   ********   ****
//   **  **    ** **   ** ** **  ** **
//   **   **  **  **      **    **  **
//   **   **  **  **      **    **  **
//   **   **  ******      **    ******
//   **  **   **  **      **    **  **
//   ****    **    **    ****  **    **
//------------------------------------------------------------------DBExport
/*
void CScriptDoc::DbExport() 
{
  CString W,W0;
  int i, j;
  CSBlock* pBS;
  CSample *pS;
  BYTE b;

	W = "Data script (*.dsc)|*.dsc|All files (*.*)|*.*||" ;
  W0 = "dsc";
  CString FileName, FileExt;
  CFileDialog dlg(FALSE, W0, m_ActDB,
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );
  FileExt = dlg.GetFileExt( ); 
  if (FileExt.IsEmpty()) FileName += "." + W0;

  TRY
  {
    CFile f(FileName,CFile::modeWrite|CFile::modeCreate);
    if (!m_DBMap.Lookup((const char*) m_ActDB, pBS)) return;
    f.Write(m_ActDB,m_ActDB.GetLength()); f.Write("\r\n",2);
    W0.Format("%u  ",pBS->GetSize());
    f.Write(W0,W0.GetLength());
    pS = pBS->GetAt(0);
    W0.Format("%u\r\n",pS->m_Values.GetSize());
    f.Write(W0,W0.GetLength());
    for (i = 0; i<pBS->GetSize(); i++)  
    {
      pS = pBS->GetAt(i);
      for (j=0; j < pS->m_Values.GetSize(); j++)
      {
        b =pS->m_Values.GetAt(j)+0x30;
        f.Write(&b,1);
      }
      f.Write("\r\n",2);
    }
  }

  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the writing file " + FileName);
  }
  END_CATCH
}

//------------------------------------------------------------------DBImport
void CScriptDoc::DbImport() 
{
  CString W,W0;
  int i, j, cSMP, cVal;
  CSBlock* pBS, *pDBS;
  CSample *pS;
  BYTE fl=0;

	W = "Data script (*.dsc)|*.dsc|All files (*.*)|*.*||" ;

  CString FileName, FileExt;
  CFileDialog dlg(TRUE, NULL, NULL,
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );

  pBS = new CSBlock;

  CFile f(FileName,CFile::modeRead);
    TRY
  {
  	CString sBuf;
  	int len;
    len = f.GetLength();
    i=0;
    while (len>0) {
      GetFileLine(f, len, sBuf);
      if (sBuf.IsEmpty())  continue;
      switch(fl) {
      case 0:  // Чтение имени блока
        pBS->m_sTitle = sBuf; fl++; break;
      case 1:  // Чтение размеров
        sscanf(sBuf, "%u %u", &cSMP, &cVal);
        fl++; break;  
      case 2:  // Чтение строки матрицы
        if(i < cSMP)
        {
          pS = new CSample;
          for (j=0; j < cVal; j++) pS->m_Values.Add(sBuf[j]-0x30);  
          pBS->Add(pS); 
          i++;
        }
      }
    } 
  }
  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the reading file " + FileName);
    return;
  }
  END_CATCH

  m_ActDB = pBS->m_sTitle;
  if (m_DBMap.Lookup((const char*) m_ActDB, pDBS)) {
    i = AfxMessageBox(IDS_EXIST_SMP,MB_YESNO);
    if (i==IDNO) {
      pBS->RemoveAll(); delete (pBS); return;
    }
    // Use old file name
    pDBS->RemoveAll(); delete (pDBS);
  }
  m_DBMap.SetAt( (const char*)m_ActDB, pBS);

  SetModifiedFlag();
  UpdateAllViews(NULL,NULL,NULL);
}


/////////////////////////////////////////////////////////////////////////////////
//  **** ***  ****  ****   ****   ****     ****
//   **  **    ****  **   **  **   **  **   **
//   ** **     ** ** **  **    **  **  **   **
//   ****      ** ** **  **    **  **  **   **
//   ** **     ** ** **  **    **   *********
//   **  **    **  ****   **  **    **** ****
//  ****  **  ****  ****   ****      **   **
//------------------------------------------------------------------KBExport
void CScriptDoc::KbExport() 
{
  CString W,W0;
  int i, j;
  CSBlock* pBS;
  CSample *pS;
  BYTE b;

	W = "Knowledge script (*.ksc)|*.ksc|All files (*.*)|*.*||" ;
  W0 = "ksc";
  CString FileName, FileExt;
  CFileDialog dlg(FALSE, W0, m_ActKB,
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );
  FileExt = dlg.GetFileExt( ); 
  if (FileExt.IsEmpty()) FileName += "." + W0;

  TRY
  {
    CFile f(FileName,CFile::modeWrite|CFile::modeCreate);
    if (!m_KBMap.Lookup((const char*) m_ActKB, pBS)) return;
    f.Write(m_ActKB,m_ActKB.GetLength()); f.Write("\r\n",2);
    W0.Format("%u  ",pBS->GetSize());
    f.Write(W0,W0.GetLength());
    pS = pBS->GetAt(0);
    W0.Format("%u\r\n",pS->m_Values.GetSize());
    f.Write(W0,W0.GetLength());
    for (i = 0; i<pBS->GetSize(); i++)  
    {
      pS = pBS->GetAt(i);
      for (j=0; j < pS->m_Values.GetSize(); j++)
      {
        b =pS->m_Values.GetAt(j)+0x30;
        f.Write(&b,1);
      }
      f.Write("\r\n",2);
    }
  }

  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the writing file " + FileName);
  }
  END_CATCH
}

//------------------------------------------------------------------KBImport
void CScriptDoc::KbImport() 
{
  CString W,W0;
  int i, j, cSMP, cVal;
  CSBlock* pBS, *pKBS;
  CSample *pS;
  BYTE fl=0;

	W = "Knowledge script (*.ksc)|*.ksc|All files (*.*)|*.*||" ;

  CString FileName, FileExt;
  CFileDialog dlg(TRUE, NULL, NULL,
	  OFN_HIDEREADONLY  | OFN_SHOWHELP | OFN_OVERWRITEPROMPT,
		W, AfxGetMainWnd());

  if (dlg.DoModal() != IDOK)  return;
  FileName =dlg.GetPathName( );

  pBS = new CSBlock;

  CFile f(FileName,CFile::modeRead);
    TRY
  {
  	CString sBuf;
  	int len;
    len = f.GetLength();
    i=0;
    while (len>0) {
      GetFileLine(f, len, sBuf);
      if (sBuf.IsEmpty())  continue;
      switch(fl) {
      case 0:  // Чтение имени блока
        pBS->m_sTitle = sBuf; fl++; break;
      case 1:  // Чтение размеров
        sscanf(sBuf, "%u %u", &cSMP, &cVal);
        fl++; break;  
      case 2:  // Чтение строки матрицы
        if(i < cSMP)
        {
          pS = new CSample;
          for (j=0; j < cVal; j++) pS->m_Values.Add(sBuf[j]-0x30);  
          pBS->Add(pS); 
          i++;
        }
      }
    } 
  }
  CATCH( CFileException, e )
  {
    AfxMessageBox("Error at the reading file " + FileName);
    return;
  }
  END_CATCH

  m_ActKB = pBS->m_sTitle;
  if (m_KBMap.Lookup((const char*) m_ActKB, pKBS)) {
    i = AfxMessageBox(IDS_EXIST_REG,MB_YESNO);
    if (i==IDNO) {
      pBS->RemoveAll(); delete (pBS); return;
    }
    // Use old file name
    pKBS->RemoveAll(); delete (pKBS);
  }
  m_KBMap.SetAt( (const char*)m_ActKB, pBS);

  SetModifiedFlag();
  UpdateAllViews(NULL,NULL,NULL);
}
*/
