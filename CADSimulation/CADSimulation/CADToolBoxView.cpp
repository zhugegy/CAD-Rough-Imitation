// CADToolBoxView.cpp : implementation file
//

#include "stdafx.h"
#include "CADSimulation.h"
#include "CADToolBoxView.h"

#include "CadDrawToolBox.h"


// CCADToolBoxView

IMPLEMENT_DYNCREATE(CCADToolBoxView, CView)

CCADToolBoxView::CCADToolBoxView()
{

}

CCADToolBoxView::~CCADToolBoxView()
{
}

BEGIN_MESSAGE_MAP(CCADToolBoxView, CView)
  ON_WM_CREATE()
  ON_WM_SIZING()
END_MESSAGE_MAP()


// CCADToolBoxView drawing

void CCADToolBoxView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CCADToolBoxView diagnostics

#ifdef _DEBUG
void CCADToolBoxView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CCADToolBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCADToolBoxView message handlers
int CCADToolBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  Add your specialized creation code here
  //GetWindowRect(&m_rcToolBoxDlg);
  
  m_pToolBoxDlg = new CCadDrawToolBox;
  m_pToolBoxDlg->Create(IDD_DIALOG_DRAWTOOLBOX, this);
  //m_pToolBoxDlg->MoveWindow(&m_rcToolBoxDlg);
  m_pToolBoxDlg->ShowWindow(SW_SHOW);


  return 0;
}


void CCADToolBoxView::OnSizing(UINT fwSide, LPRECT pRect)
{
  CView::OnSizing(fwSide, pRect);

  // TODO: Add your message handler code here
//   m_rcToolBoxDlg = pRect;
//   m_pToolBoxDlg->MoveWindow(m_rcToolBoxDlg);

}
