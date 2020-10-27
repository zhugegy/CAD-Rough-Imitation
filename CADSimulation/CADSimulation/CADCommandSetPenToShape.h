#pragma once
#include "CADCommand.h"

#include "CADShape.h"

class CADCommandSetPenToShape :
    public CADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeSetPenTo;

  int m_nPenWidthBefore;
  int m_nPenStyleBefore;
  COLORREF m_nPenColorBefore;

  int m_nPenWidthAfter;
  int m_nPenStyleAfter;
  COLORREF m_nPenColorAfter;
};

