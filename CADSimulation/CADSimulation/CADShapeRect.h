#pragma once
#include "CADShape.h"
class CCADShapeRect :
  public CCADShape
{
  DECLARE_SERIAL(CCADShapeRect)

public:
  CCADShapeRect();
  virtual ~CCADShapeRect();

  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  void Serialize(CArchive& archive);

};

