#pragma once
#include "ICADCommand.h"

#include "CADShape.h"

class CADCommandDeleteShape :
    public ICADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  CCADShape* m_pShapeDeleted;
};

