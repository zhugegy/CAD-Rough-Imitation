#pragma once
#include "ICADCommand.h"

#include "CADShape.h"

class CADCommandAddShape :
    public ICADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeAdded;
};

