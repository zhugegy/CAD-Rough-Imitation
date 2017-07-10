#pragma once
#include "CADShape.h"
class CCADShapeEllipse :
  public CCADShape
{
public:
  CCADShapeEllipse();
  virtual ~CCADShapeEllipse();
  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);

};

