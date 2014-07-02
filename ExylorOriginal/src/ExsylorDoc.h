// ExsylorDoc.h : interface of the CExsylorDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXSYLORDOC_H__FF7FCE66_ECEB_44F2_872F_C4DB2F380462__INCLUDED_)
#define AFX_EXSYLORDOC_H__FF7FCE66_ECEB_44F2_872F_C4DB2F380462__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExsylorDoc : public CDocument
{
protected: // create from serialization only
	CExsylorDoc();
	DECLARE_DYNCREATE(CExsylorDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExsylorDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExsylorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CExsylorDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXSYLORDOC_H__FF7FCE66_ECEB_44F2_872F_C4DB2F380462__INCLUDED_)
