// Exsylor.h : main header file for the EXSYLOR application
//

#if !defined(AFX_EXSYLOR_H__FB332E3E_C14C_4F52_9B75_26157406F0DF__INCLUDED_)
#define AFX_EXSYLOR_H__FB332E3E_C14C_4F52_9B75_26157406F0DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif


class CModelScript;
class CSBlock;

#include "resource.h"       // main symbols

extern char Symbol0;
//------------------------------ Task table
#define NEW_SAMPLE 1  // New date
#define EDIT_DB    2  // Edit data
#define NEW_REGUL  4  // New knowledge
#define EDIT_KB    8  // Edit knowledge
#define OBJECT     16 // Object description
#define KNOW_RED   32 // Knowledge reduction
#define AIM_FULL   64 // Recognition - select FULL
#define AIM_ATR   128 // Recognition - select attribute
#define AIM_VAL   256 // Recognition - select value
#define AIM  (AIM_VAL | AIM_ATR | AIM_FULL | OBJECT)

#define EXPLAN    512  // Recognition - select value
#define IND_DB    1024 // Induction
#define GEN_DB    2048 // Data generation

//------------------------------ Frame table
#define MODVIEW    1
#define DBVIEW     2
#define KBVIEW     3
#define OBVIEW     4
#define RESVIEW    5
#define BMVIEW     6
#define EXPLANVIEW 7

/////////////////////////////////////////////////////////////////////////////
// CExsylorApp:
// See Exsylor.cpp for the implementation of this class
//

class CExsylorApp : public CWinApp
{
public:
	CExsylorApp();

    int CurrentTask;
//945    int m_System;
    CString BazePath;
    int  m_nActiveFrame;

    CMultiDocTemplate* pScriptDocTemplate;
    CMultiDocTemplate* pRegulTemplate;
    CMultiDocTemplate* pRegulEditTemplate;
    CMultiDocTemplate* pWordScriptTemplate;
    CMultiDocTemplate* pWordEditTemplate;
    CMultiDocTemplate* pObjectTemplate;
    CMultiDocTemplate* pAimTemplate;
    CMultiDocTemplate* pExsDocTemplate;
    CMultiDocTemplate* pViewBMTemplate;
    CMultiDocTemplate* pViewExplanTemplate;
    CMultiDocTemplate* pViewIndTemplate;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExsylorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
   void UpdateIniFileWithDocPath(const char* pszPathName);
   CString GetDocPathFromIniFile();

	//{{AFX_MSG(CExsylorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
extern CExsylorApp theApp;

extern void GetFileLine(CFile& f, int& len, CString& s);
// Читать очередную строку текстового файла:
//  f - объект файл, len - оставшаяся длина файла, s - считанная строка

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXSYLOR_H__FB332E3E_C14C_4F52_9B75_26157406F0DF__INCLUDED_)
