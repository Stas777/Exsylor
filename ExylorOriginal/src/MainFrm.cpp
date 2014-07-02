// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Exsylor.h"

#include "MainFrm.h"
#include "scrdoc.h"
#include "brview.h"
#include "trbzview.h"
#include "treeview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
    ON_UPDATE_COMMAND_UI(ID_INDICATOR_TASK, OnUpdateTask)
    ON_WM_CLOSE()
    ON_COMMAND(ID_RECOGNITION, OnRecognition)
    ON_UPDATE_COMMAND_UI(ID_RECOGNITION, OnUpdateRecognition)
	//}}AFX_MSG_MAP
    // Global help commands
    ON_COMMAND(ID_HELP_INDEX, CMDIFrameWnd::OnHelpIndex)
    ON_COMMAND(ID_HELP_USING, CMDIFrameWnd::OnHelpUsing)
    ON_COMMAND(ID_HELP, CMDIFrameWnd::OnHelp)
    ON_COMMAND(ID_CONTEXT_HELP, CMDIFrameWnd::OnContextHelp)
    ON_COMMAND(ID_DEFAULT_HELP, CMDIFrameWnd::OnHelpIndex)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
  ID_INDICATOR_TASK,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame() {}

CMainFrame::~CMainFrame() {}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
  
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return TRUE;
}

void CMainFrame::OnReplaceMenu(int MenuID) 
{
  if ((UINT)m_NewMenu.m_hMenu !=NULL)
    m_NewMenu.DestroyMenu();

  // Load the new menu.
   m_NewMenu.LoadMenu(MenuID);

   ASSERT(m_NewMenu);

   // Remove and destroy the old menu
   SetMenu(NULL);

   // Add the new menu
   SetMenu(&m_NewMenu);

   // Assign default menu
   m_hMenuDefault = m_NewMenu.GetSafeHmenu();  // or m_NewMenu.m_hMenu;
}

//-----------------------------------------------------------------CreateOrActivateFrame
void CMainFrame::CreateOrActivateFrame(CDocTemplate* pTemplate, CRuntimeClass* pViewClass)
{
 CMDIChildWnd* pNewFrame;
 CMDIChildWnd* pMDIActive = MDIGetActive();
 ASSERT(pMDIActive != NULL);
 CDocument* pDoc = pMDIActive->GetActiveDocument();
 ASSERT(pDoc != NULL);

 CView* pView;
 POSITION pos = pDoc->GetFirstViewPosition();
 while (pos != NULL) {
   pView = pDoc->GetNextView(pos);
   if (pView->IsKindOf(pViewClass)) {
     pView->GetParentFrame()->ActivateFrame();
     pView->GetParentFrame()->SetActiveView(pView);
     pDoc->UpdateAllViews(NULL,0L,NULL);
     goto end00;
   }
 }

 pNewFrame = (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
 if (pNewFrame != NULL) {     // not created
   ASSERT(pNewFrame->IsKindOf(RUNTIME_CLASS(CMDIChildWnd)));
   pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
 }  // else // not created
end00:
 if (pTemplate == theApp.pExsDocTemplate) {
   ViewRec(); theApp.m_nActiveFrame=OBVIEW; return;
 }
 if (pTemplate == theApp.pScriptDocTemplate) {
   ViewMod(); theApp.m_nActiveFrame=MODVIEW; return;
 }
 if (pTemplate == theApp.pWordScriptTemplate) {
   ViewDB();  theApp.m_nActiveFrame=DBVIEW;   return;
 }
 if (pTemplate == theApp.pWordEditTemplate) {
   ViewDBEdit(); theApp.m_nActiveFrame=DBVIEW; return;
 }
 if (pTemplate == theApp.pRegulTemplate) {
   ViewKB();  theApp.m_nActiveFrame=KBVIEW; return;
 }
 if (pTemplate == theApp.pRegulEditTemplate) {
   ViewKBEdit(); theApp.m_nActiveFrame=KBVIEW; return;
 }
 if (pTemplate == theApp.pObjectTemplate) {
   ViewRec(); theApp.m_nActiveFrame=OBVIEW; return;
 }
 if (pTemplate == theApp.pAimTemplate) {
   ViewRec(); theApp.m_nActiveFrame=RESVIEW; return;
 }
 if (pTemplate == theApp.pViewBMTemplate) {
   ViewBM(); theApp.m_nActiveFrame=BMVIEW; return;
 }
 if (pTemplate == theApp.pViewExplanTemplate) {
   ViewExplan(); theApp.m_nActiveFrame=EXPLANVIEW; return;
 }
 
}



//--------------------------------------------------------------------ViewOut
void CMainFrame::ViewOut()
{
  if (!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_MAINFRAME);
}

//--------------------------------------------------------------------ViewMod
void CMainFrame::ViewMod()
{ 
  if (!m_wndToolBar.LoadToolBar(IDR_SCROPTTYPE)) {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_SCROPTTYPE);
}


//--------------------------------------------------------------------ViewDB
void CMainFrame::ViewDB()
{
  if (!m_wndToolBar.LoadToolBar(IDR_WORD_SCRIPT))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_WORD_SCRIPT);
}

//--------------------------------------------------------------------ViewDBEdit
void CMainFrame::ViewDBEdit()
{
  if (!m_wndToolBar.LoadToolBar(IDR_WORD_EDIT))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_WORD_EDIT);
}

//--------------------------------------------------------------------ViewKB
void CMainFrame::ViewKB()
{
  if (!m_wndToolBar.LoadToolBar(IDR_REG_SCRIPT))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_REG_SCRIPT);
}

//--------------------------------------------------------------------ViewKBEdit
void CMainFrame::ViewKBEdit()
{
  if (!m_wndToolBar.LoadToolBar(IDR_REG_EDIT))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_REG_EDIT);
}

//--------------------------------------------------------------------ViewRec
void CMainFrame::ViewRec()
{
  if (!m_wndToolBar.LoadToolBar(IDR_EXSTYPE))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_EXSTYPE);
}

//--------------------------------------------------------------------ViewBM
void CMainFrame::ViewBM()
{
  if (!m_wndToolBar.LoadToolBar(IDR_EMPTY))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_EMPTY);
}

//--------------------------------------------------------------------ViewExplan
void CMainFrame::ViewExplan()
{
  if (!m_wndToolBar.LoadToolBar(IDR_EXPLAN))  {
    TRACE("Failed to create toolbar\n");
    return;      // fail to create
  }
  m_wndToolBar.Invalidate();
  OnReplaceMenu(IDR_EXPLAN);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{	CMDIFrameWnd::AssertValid(); }
void CMainFrame::Dump(CDumpContext& dc) const
{	CMDIFrameWnd::Dump(dc); }
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
/////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------OnUpdateTask
void CMainFrame::OnUpdateTask(CCmdUI* pCmdUI)
{ CString W;
 CDocument* pDoc;
 CMDIChildWnd* pMDIActive = MDIGetActive();
 
 if (pMDIActive == NULL) goto n1;
 if ((pDoc = pMDIActive->GetActiveDocument()) == NULL) { 
n1: W.LoadString(IDS_SYSMODE); goto n2;
 }
 
 switch (theApp.m_nActiveFrame) {
 case MODVIEW: W.LoadString(IDS_SYSTEM); break; 
 
 case DBVIEW:  if (theApp.CurrentTask & NEW_SAMPLE) W.LoadString(IDS_CR_DATA);
               else  W.LoadString(IDS_ED_DATA);
               break;
               
 case KBVIEW:  if (theApp.CurrentTask & NEW_REGUL) W.LoadString(IDS_CR_KNOW);
               else  W.LoadString(IDS_ED_KNOW);
               break;
 
 case OBVIEW:  if (theApp.CurrentTask & OBJECT) W.LoadString(IDS_DESC_OBJ); 
               else  W.LoadString(IDS_CH_AIM);
               break;
 case BMVIEW: W.LoadString(IDS_BMVIEW); break; 
 
 case EXPLANVIEW: W.LoadString(IDS_EXPLANVIEW); break; 
 default :  pCmdUI->Enable(FALSE); return; 
 }
n2: pCmdUI->Enable(TRUE); m_wndStatusBar.SetPaneText(1,W,TRUE);
}

//--------------------------------------------------------------------OnClose
void CMainFrame::OnClose()
{ if(theApp.CurrentTask>0) 
    if (AfxMessageBox(IDS_REALLY,MB_YESNO)!=IDYES) return;
  CMDIFrameWnd::OnClose(); theApp.CurrentTask = 0; theApp.m_nActiveFrame=0;
}


/////////////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------OnRecognition
void CMainFrame::OnRecognition()
{
 CMDIChildWnd* pMDIActive = MDIGetActive();
 if (pMDIActive == NULL) return; 
 CScriptDoc* pDoc = (CScriptDoc*)pMDIActive->GetActiveDocument();
 pDoc->RecognObject();
 CreateOrActivateFrame(theApp.pObjectTemplate, RUNTIME_CLASS(CTrObView));
}

//--------------------------------------------------------------------OnUpdateRecognition
void CMainFrame::OnUpdateRecognition(CCmdUI* pCmdUI)
{
  CMDIChildWnd* pMDIActive = MDIGetActive();
  if (pMDIActive == NULL) { pCmdUI->Enable(FALSE); return; }
  CScriptDoc* pDoc = (CScriptDoc*)pMDIActive->GetActiveDocument();
  if (pDoc == NULL)       { pCmdUI->Enable(FALSE); return; }
  pCmdUI->Enable(theApp.CurrentTask==0 &&       //Общий режим
                 pDoc->m_KBMap.GetCount()>0 &&  //Есть знания
                 !pDoc->m_ActKB.IsEmpty());     //Выбран активный блок знаний
}

//--------------------------------------------------------------------OnSystem
/*void CMainFrame::OnSystem()
{ CMDIChildWnd* pMDIActive = MDIGetActive();
 if (pMDIActive == NULL) return; 
 if (theApp.m_System) {
   pMDIActive->MDIDestroy();
   pMDIActive = MDIGetActive();
   if (pMDIActive == NULL) {
     ViewOut(); theApp.m_nActiveFrame=0; theApp.CurrentTask=0;
   }
   else {
     ViewMod(); theApp.m_nActiveFrame=MODVIEW;theApp.CurrentTask&=~(AIM);
   }  
 }  
 else { theApp.m_System = TRUE; ViewMod(); }
}


//--------------------------------------------------------------------OnUpdateSystem
void CMainFrame::OnUpdateSystem(CCmdUI* pCmdUI) { }

*/