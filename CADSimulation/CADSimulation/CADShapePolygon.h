#pragma once
#include "CADShape.h"
class CCADShapePolygon :
  public CCADShape
{
public:
  CCADShapePolygon();
  virtual ~CCADShapePolygon();

  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  /*==virtual==*/ BOOL IsSelected(LPRECT pUserRect);
  /*==virtual==*/ int WhenDragged(int nCoordXOffset, int nCoordYOffset);
  /*==virtual==*/ int BeforeBeingDragged();

public:
  int m_nPointCount;
  POINT m_aryPoints[10];
  POINT m_aryTransferedPoints[10];
  POINT m_aryTransferedPointsBefore[10];


private:
  int TransferPolygonPoints();
};

