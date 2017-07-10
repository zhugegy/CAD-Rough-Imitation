#pragma once
#include "CADShape.h"
class CCADShapeEllipse :
  public CCADShape
{
  DECLARE_SERIAL(CCADShapeEllipse)

public:
  CCADShapeEllipse();
  virtual ~CCADShapeEllipse();
  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  void Serialize(CArchive& archive);

};

