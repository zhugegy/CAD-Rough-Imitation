#include "stdafx.h"
#include "CADCommandDeleteShapes.h"

//#include "CADSimulation.h"
//#include "CADStorage.h"


void CADCommandDeleteShapes::UnExecute()
{
  for (int i = 0; i < m_vctDeleteShapeCommands.size(); i++)
  {
    m_vctDeleteShapeCommands[i]->UnExecute();
  }
}

void CADCommandDeleteShapes::ReExecute()
{
  for (int i = 0; i < m_vctDeleteShapeCommands.size(); i++)
  {
    m_vctDeleteShapeCommands[i]->ReExecute();
  }
}

int CADCommandDeleteShapes::PushDeleteShapeCommand(CADCommandDeleteShape* pCmd)
{
  m_vctDeleteShapeCommands.push_back(pCmd);

  return 0;
}

int CADCommandDeleteShapes::GetCommandCount()
{
  return m_vctDeleteShapeCommands.size();
}
