// Exsylor.cpp : Defines the class behaviors for the application.
//
#include <stdio.h>
#include <direct.h>

#include "stdafx.h"
#include "Exsylor.h"

#include "scrdoc.h"
#include "splitter.h"

#include "MainFrm.h"
#include "ChildFrm.h"

#include "brView.h"
#include "ModView.h"
#include "WordView.h"
#include "bmview.h"
#include "trbzview.h"
#include "treeview.h"
#include "FormInd.h"
#include "scriptvw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static char BASED_CODE szIniFileEntry[] = "File";
char  szIniFileSection[] = "Exsylor Most Recent File";
char Symbol0='.';

/////////////////////////////////////////////////////////////////////////////
// CExsylorApp

BEGIN_MESSAGE_MAP(CExsylorApp, CWinApp)
	//{{AFX_MSG_MAP(CExsylorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CExsylorApp construction

CExsylorApp::CExsylorApp()
{
  CurrentTask = -1;
  BazePath +="..\\data";
  _chdir(BazePath);
  BazePath +="\\";
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CExsylorApp object

CExsylorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CExsylorApp initialization

BOOL CExsylorApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
//945  m_System = TRUE;

    pScriptDocTemplate = new CMultiDocTemplate(
        IDR_SCRIPTTYPE,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitModFrame),        // standard MDI child frame
        RUNTIME_CLASS(CModView));
    AddDocTemplate(pScriptDocTemplate);

    pRegulTemplate = new CMultiDocTemplate(
        IDR_REG_SCRIPT,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitKBFrame),        // standard MDI child frame
        RUNTIME_CLASS(CWordRegView));
    AddDocTemplate(pRegulTemplate);

    pWordScriptTemplate = new CMultiDocTemplate(
        IDR_WORD_SCRIPT,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitDBFrame),        // standard MDI child frame
        RUNTIME_CLASS(CWordView));
    AddDocTemplate(pWordScriptTemplate);

    pWordEditTemplate = new CMultiDocTemplate(
        IDR_WORD_EDIT,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitDBEditFrame),        // standard MDI child frame
        RUNTIME_CLASS(CWordView));
    AddDocTemplate(pWordEditTemplate);

    pRegulEditTemplate = new CMultiDocTemplate(
        IDR_REG_EDIT,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitKBEditFrame),        // standard MDI child frame
        RUNTIME_CLASS(CWordRegView));
    AddDocTemplate(pRegulEditTemplate);

    pObjectTemplate = new CMultiDocTemplate(
        IDR_EXSTYPE,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitRecognFrame),    // standard MDI child frame
        RUNTIME_CLASS(CRecogScriptView));
    AddDocTemplate(pObjectTemplate);

    pAimTemplate = new CMultiDocTemplate(
        IDR_EXSTYPE,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitRecognFrame),    // standard MDI child frame
        RUNTIME_CLASS(CRecogScriptView));
    AddDocTemplate(pAimTemplate);

    pExsDocTemplate = new CMultiDocTemplate(
        IDR_EXSTYPE,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitRecognFrame),    // standard MDI child frame
        RUNTIME_CLASS(CRecogScriptView));
    AddDocTemplate(pExsDocTemplate);
    
    pViewBMTemplate = new CMultiDocTemplate(
        IDR_EMPTY,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitViewBMFrame),    // standard MDI child frame
        RUNTIME_CLASS(CBM_View));
    AddDocTemplate(pViewBMTemplate);
    
    pViewExplanTemplate = new CMultiDocTemplate(
        IDR_EXPLAN,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CSplitExplanFrame),    // standard MDI child frame
        RUNTIME_CLASS(CExplanStepView));
    AddDocTemplate(pViewExplanTemplate);
    
    pViewIndTemplate = new CMultiDocTemplate(
        IDR_SCRIPTTYPE,
        RUNTIME_CLASS(CScriptDoc),
        RUNTIME_CLASS(CIndWnd),    // standard MDI child frame
        RUNTIME_CLASS(CFormInd));
    AddDocTemplate(pViewIndTemplate);
    
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
//	CCommandLineInfo cmdInfo;
//	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
//	if (!ProcessShellCommand(cmdInfo))
//		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pMainFrame->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CExsylorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CExsylorApp message handlers

/////////////////////////////////////////////////////////////////////////////
//----------------------------------------------------------------
// INI file implementation ---------------------------------------
//----------------------------------------------------------------

//----------------------------------------------------------------
void CExsylorApp::UpdateIniFileWithDocPath(const char* pszPathName)
{ WriteProfileString(szIniFileSection, szIniFileEntry, pszPathName); }

//----------------------------------------------------------------
CString CExsylorApp::GetDocPathFromIniFile()
{ return GetProfileString(szIniFileSection, szIniFileEntry, NULL); }

/////////////////////////////////////////////////////////////////////////////
