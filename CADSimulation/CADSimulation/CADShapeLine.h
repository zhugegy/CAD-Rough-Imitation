#pragma once
#include "CADShape.h"
class CCADShapeLine :
  public CCADShape
{
public:
  CCADShapeLine();
  virtual ~CCADShapeLine();
  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  /*==virtual==*/ BOOL IsSelected(LPRECT pUserRect);

};

