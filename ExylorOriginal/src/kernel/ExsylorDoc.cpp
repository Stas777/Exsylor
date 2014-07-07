// ExsylorDoc.cpp : implementation of the CExsylorDoc class
//

#include "stdafx.h"
#include "Exsylor.h"

#include "ExsylorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExsylorDoc

IMPLEMENT_DYNCREATE(CExsylorDoc, CDocument)

BEGIN_MESSAGE_MAP(CExsylorDoc, CDocument)
	//{{AFX_MSG_MAP(CExsylorDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExsylorDoc construction/destruction

CExsylorDoc::CExsylorDoc()
{
	// TODO: add one-time construction code here

}

CExsylorDoc::~CExsylorDoc()
{
}

BOOL CExsylorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CExsylorDoc serialization

void CExsylorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CExsylorDoc diagnostics

#ifdef _DEBUG
void CExsylorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CExsylorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExsylorDoc commands
