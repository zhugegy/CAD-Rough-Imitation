#pragma once
#include "ICADCommand.h"
#include <vector>
using namespace std;

#include "CADShape.h"
#include "CADCommandDeleteShape.h"

class CADCommandDeleteShapes :
  public ICADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  int PushDeleteShapeCommand(CADCommandDeleteShape* pCmd);
  int GetCommandCount();

private:
  vector <CADCommandDeleteShape *> m_vctDeleteShapeCommands;
};

