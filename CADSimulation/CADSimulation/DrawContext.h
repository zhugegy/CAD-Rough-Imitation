#pragma once

#include "CADShape.h"

class CDrawContext
{
public:
  CDrawContext();
  CDrawContext(CString &strShapeName);

  virtual ~CDrawContext();
private:
  CCADShape* m_pobjCurrentShape;
public:
  int SetShape();

  int OnLButtonDown(CPoint & objPoint);
  int OnLButtonUp(CPoint & objPoint);
  int OnMouseMove(CPoint & objPoint);
  int Draw(HWND hWnd, CDC * pDC);
};

