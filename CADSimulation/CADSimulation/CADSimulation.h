
// CADSimulation.h : main header file for the CADSimulation application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CCADSimulationApp:
// See CADSimulation.cpp for the implementation of this class
//

#include "CADShape.h"
#include "CADSimulationView.h"

class CCADSimulationApp : public CWinAppEx
{
public:
	CCADSimulationApp();

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
  CString * GetLastShapeName();
  int SetLastShapeName(CWnd * pShapeButton);

  int m_nPenWidth;
  int m_nPenStyle;
  COLORREF  m_nPenColor;
  COLORREF  m_nBrushColor;

  POINT m_aryCustomizedShapePoints[10];
  int m_nCustomiezedShapePointCount;

  CList<CCADShape *, CCADShape *> m_lstSelectedShapes;

  CCADSimulationView *m_pView;

private:
  CString m_strLastShapeName;
};

extern CCADSimulationApp theApp;
