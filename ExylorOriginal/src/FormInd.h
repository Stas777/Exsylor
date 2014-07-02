// formind.h : header file
// 17.05.2007
//------------------------

/////////////////////////////////////////////////////////////////////////////
// CFormInd form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

class CFormInd : public CFormView
{
	DECLARE_DYNCREATE(CFormInd)
protected:
	CFormInd();			// protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CFormInd)
	enum { IDD = IDD_IND_TABLE };
	int		m_Num_Con;
	int		m_LimRank;
	double	m_LimProb;
	int		m_LimNum;
	int		m_Rank;
	int		m_Number;
	double	m_Prob;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:
   void OnUpdate(CView*, LPARAM lHint, CObject* pHint);

// Implementation
protected:
	virtual ~CFormInd();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	// Generated message map functions
	//{{AFX_MSG(CFormInd)
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
