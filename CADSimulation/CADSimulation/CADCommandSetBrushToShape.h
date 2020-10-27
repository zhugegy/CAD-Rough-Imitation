#pragma once
#include "CADCommand.h"

#include "CADShape.h"

class CADCommandSetBrushToShape :
    public CADCommand
{
public:
  /*==virtual==*/ void UnExecute();
  /*==virtual==*/ void ReExecute();

  CCADShape* m_pShapeSetBrushTo;

  COLORREF m_nBrushColorBefore;
  COLORREF m_nBrushColorAfter;
};

