#pragma once
#include "CADCommand.h"

#include "CADShape.h"

class CADCommandRotateShape :
    public CADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeRotated;
  int m_nRotationDegreeBefore;
  int m_nRotationDegreeAfter;
};

