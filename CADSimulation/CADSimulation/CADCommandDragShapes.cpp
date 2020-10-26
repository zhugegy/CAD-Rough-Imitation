#include "stdafx.h"
#include "CADCommandDragShapes.h"



void CADCommandDragShapes::UnExecute()
{
  for (int i = 0; i < m_vctDragShapeCommands.size(); i++)
  {
    m_vctDragShapeCommands[i]->UnExecute();
  }
}

void CADCommandDragShapes::ReExecute()
{
  for (int i = 0; i < m_vctDragShapeCommands.size(); i++)
  {
    m_vctDragShapeCommands[i]->ReExecute();
  }
}

int CADCommandDragShapes::PushDragShapeCommand(CADCommandDragShape* pCmd)
{
  m_vctDragShapeCommands.push_back(pCmd);

  return 0;
}

int CADCommandDragShapes::GetCommandCount()
{
  return m_vctDragShapeCommands.size();
}
