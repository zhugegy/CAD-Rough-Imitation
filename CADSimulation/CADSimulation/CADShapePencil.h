#pragma once
#include "CADShape.h"
class CCADShapePencil :
  public CCADShape
{
  DECLARE_SERIAL(CCADShapePencil)

public:
  CCADShapePencil();
  virtual ~CCADShapePencil();
  /*==virtual==*/ CDC * Draw(HWND hWnd, CDC * pDC);
  /*==virtual==*/ int SetEndPoint(CPoint & objEndPoint);
  /*==virtual==*/ int WhenDragged(int nCoordXOffset, int nCoordYOffset);
  /*==virtual==*/ int WhenDraggedCommandMode(int nCoordXOffset, int nCoordYOffset);
  /*==virtual==*/ int WhenUndraggedCommandMode(CPoint& ptBegin, CPoint& ptEnd);
  /*==virtual==*/ int BeforeBeingDragged();

  

  void Serialize(CArchive& archive);

private:
  CList<CPoint, CPoint> m_lstPencilPoints;
  CList<CPoint, CPoint> m_lstPencilPointsBefore;

};

