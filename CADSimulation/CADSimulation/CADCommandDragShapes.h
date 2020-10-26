#pragma once
#include "ICADCommand.h"
#include <vector>
using namespace std;

#include "CADShape.h"
#include "CADCommandDragShape.h"

class CADCommandDragShapes :
  public ICADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  int PushDragShapeCommand(CADCommandDragShape* pCmd);
  int GetCommandCount();

private:
  vector <CADCommandDragShape *> m_vctDragShapeCommands;
};

