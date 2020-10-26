#pragma once
#include "ICADCommand.h"

#include "CADShape.h"

class CADCommandDragShape :
    public ICADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeDragged;

  void SetOriginPoint(CPoint& ptStartPTBeforeDragged, CPoint& ptEndPTBeforeDragged);
  void SetOffsets(int x, int y);

private:
  CPoint m_ptStartPTBeforeDragged;
  CPoint m_ptEndPTBeforeDragged;

  int m_nCoordXOffset;
  int m_nCoordYOffset;
};

