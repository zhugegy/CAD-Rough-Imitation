
// CADSimulationView.cpp : implementation of the CCADSimulationView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CADSimulation.h"
#endif

#include "CADSimulationDoc.h"
#include "CADSimulationView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "CADLineStyleDialog.h"

extern CCADSimulationApp theApp;


// CCADSimulationView

IMPLEMENT_DYNCREATE(CCADSimulationView, CView)

BEGIN_MESSAGE_MAP(CCADSimulationView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEMOVE()
  ON_COMMAND(ID_CAD_TOOLBAR_LINE, &CCADSimulationView::OnCadToolbarLine)
  ON_WM_CREATE()
END_MESSAGE_MAP()

// CCADSimulationView construction/destruction

CCADSimulationView::CCADSimulationView()
{
	// TODO: add construction code here
  m_pobjDrawContext = NULL;
  m_pobjDrawContext = new CDrawContext;

  m_bIsDrawing = false;

  theApp.m_pView = this;
}

CCADSimulationView::~CCADSimulationView()
{
  if (m_pobjDrawContext != NULL)
  {
    delete m_pobjDrawContext;
    m_pobjDrawContext = NULL;
  }
}

BOOL CCADSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCADSimulationView drawing

void CCADSimulationView::OnDraw(CDC* pDC)
{
	CCADSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

  m_pobjDrawContext->Draw(GetSafeHwnd(), pDC);

	// TODO: add draw code for native data here
}


// CCADSimulationView printing

BOOL CCADSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCADSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCADSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CCADSimulationView diagnostics

#ifdef _DEBUG
void CCADSimulationView::AssertValid() const
{
	CView::AssertValid();
}

void CCADSimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCADSimulationDoc* CCADSimulationView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCADSimulationDoc)));
	return (CCADSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CCADSimulationView message handlers


void CCADSimulationView::OnLButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  m_bIsDrawing = true;

  m_pobjDrawContext->OnLButtonDown(point);

  SetCapture();

  CView::OnLButtonDown(nFlags, point);
}


void CCADSimulationView::OnLButtonUp(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  m_bIsDrawing = false;
  m_pobjDrawContext->OnLButtonUp(point);
  
  //通知窗口进行重绘
  InvalidateRect(NULL, FALSE);
  
  ReleaseCapture();

  CView::OnLButtonUp(nFlags, point);
}


void CCADSimulationView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  if (m_bIsDrawing == true)
  {
    m_pobjDrawContext->OnMouseMove(point);

    //通知窗口进行重绘
    InvalidateRect(NULL, FALSE);
  }

  CView::OnMouseMove(nFlags, point);
}


void CCADSimulationView::OnCadToolbarLine()
{
  // TODO: Add your command handler code here
  AfxMessageBox(_T("OKK"));
}


int CCADSimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
  if (CView::OnCreate(lpCreateStruct) == -1)
    return -1;

  // TODO:  Add your specialized creation code here
  return 0;
}