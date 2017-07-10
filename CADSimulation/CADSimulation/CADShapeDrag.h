#pragma once
#include "CADShape.h"
class CCADShapeDrag :
  public CCADShape
{
public:
  CCADShapeDrag();
  virtual ~CCADShapeDrag();

  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  /*==virtual==*/ int SaveThisShape(CPoint & objPoint);
  /*==virtual==*/ int SetBeginPoint(CPoint & objBeginPoint);
  /*==virtual==*/ int SetEndPoint(CPoint & objBeginPoint);

};

