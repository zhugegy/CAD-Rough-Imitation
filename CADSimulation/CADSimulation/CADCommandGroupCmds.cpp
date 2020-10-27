#include "stdafx.h"
#include "CADCommandGroupCmds.h"

void CADCommandGroupCmds::UnExecute()
{
  for (int i = 0; i < m_vctCommands.size(); i++)
  {
    m_vctCommands[i]->UnExecute();
  }
}

void CADCommandGroupCmds::ReExecute()
{
  for (int i = 0; i < m_vctCommands.size(); i++)
  {
    m_vctCommands[i]->ReExecute();
  }
}

int CADCommandGroupCmds::PushCommand(CADCommand* pCmd)
{
  m_vctCommands.push_back(pCmd);

  return 0;
}

int CADCommandGroupCmds::GetCommandCount()
{
  return m_vctCommands.size();
}
