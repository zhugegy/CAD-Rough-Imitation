#pragma once
#include "CADShape.h"
class CCADShapeRect :
  public CCADShape
{
public:
  CCADShapeRect();
  virtual ~CCADShapeRect();

  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);

};

