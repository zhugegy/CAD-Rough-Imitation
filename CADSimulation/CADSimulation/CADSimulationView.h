
// CADSimulationView.h : interface of the CCADSimulationView class
//

#pragma once

#include "DrawContext.h"
#include "CADSimulationDoc.h"

class CCADSimulationView : public CView
{
protected: // create from serialization only
	CCADSimulationView();
	DECLARE_DYNCREATE(CCADSimulationView)

// Attributes
public:
	CCADSimulationDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CCADSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);

private:
  CDrawContext *m_pobjDrawContext;
  bool m_bIsDrawing;
public:
  afx_msg void OnCadToolbarLine();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
protected:
public:
	afx_msg void OnRightbuttonpopupDelete();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRightbuttonpopupChangeShapePen();
	afx_msg void OnRightbuttonpopupChangeShapeBrush();
};

#ifndef _DEBUG  // debug version in CADSimulationView.cpp
inline CCADSimulationDoc* CCADSimulationView::GetDocument() const
   { return reinterpret_cast<CCADSimulationDoc*>(m_pDocument); }
#endif

