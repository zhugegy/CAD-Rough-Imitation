#pragma once
#include "CADCommand.h"

#include "CADShape.h"

class CADCommandAddShape :
    public CADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeAdded;
};

