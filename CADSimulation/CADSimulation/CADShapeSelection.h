#pragma once
#include "CADShape.h"
class CCADShapeSelection :
  public CCADShape
{
public:
  CCADShapeSelection();
  virtual ~CCADShapeSelection();

  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  /*==virtual==*/ int SaveThisShape(CPoint & objPoint);
private:
  int FindSelectedShapes();
  bool m_bIsSelectionDone;
};

