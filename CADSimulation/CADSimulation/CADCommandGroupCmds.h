#pragma once
#include "CADCommand.h"
#include <vector>
using namespace std;

#include "CADShape.h"

class CADCommandGroupCmds :
  public CADCommand
{
public:
  /*virtual*/ void UnExecute();
  /*virtual*/ void ReExecute();

  int PushCommand(CADCommand* pCmd);
  int GetCommandCount();

private:
  vector <CADCommand*> m_vctCommands;
};

