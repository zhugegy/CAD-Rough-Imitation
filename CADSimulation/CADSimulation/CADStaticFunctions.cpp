#include "stdafx.h"

#include "CADStaticFunctions.h"
#include "CADSimulation.h"

#include "CADStorage.h"
#include "CADCommand.h"
#include "CADCommandGroupCmds.h"
#include "CADCommandDeleteShape.h"

#include <afxwin2.inl>

int CADStaticFunctions::delete_shapes()
{
  //������ǰѡ��
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  if (posSelected == NULL)
  {
    return -1;
  }

  CADCommandGroupCmds* pCmdDeleteShapes = new CADCommandGroupCmds;

  while (posSelected)
  {
    CCADShape* pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    POSITION posToDelete = pStorage->m_lstShapes.Find(pShape);
    if (posToDelete)
    {
      pStorage->m_lstShapes.RemoveAt(posToDelete);

      CADCommandDeleteShape* pCmdDeleteShape = new CADCommandDeleteShape;
      pCmdDeleteShape->m_pShapeDeleted = pShape;
      pCmdDeleteShapes->PushCommand(pCmdDeleteShape);
    }
  }

  ASSERT(pCmdDeleteShapes->GetCommandCount() != 0);

  if (pCmdDeleteShapes->GetCommandCount())
  {
    pStorage->m_stkToUndo.push(pCmdDeleteShapes);
  }

  return 0;
}

int CADStaticFunctions::unselect_all()
{
  //��յ�ǰѡ��
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape* pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->WhenUnselected();
  }

  (theApp.m_lstSelectedShapes).RemoveAll();

  return 0;
}

void CADStaticFunctions::Undo()
{
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  if (pStorage->m_stkToUndo.empty())
  {
    return;
  }

  //����
  CADCommand* pCmd = pStorage->m_stkToUndo.top();
  pCmd->UnExecute(); 
  pStorage->m_stkToUndo.pop();

  pStorage->m_stkToRedo.push(pCmd);  //������һ��ջ��,�ȴ���ִ������
}

void CADStaticFunctions::Redo()
{
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  //ջΪ��, ˵��û�в�����Ҫ������
  if (pStorage->m_stkToRedo.empty())
  {
    return;
  }

  //����
  CADCommand* pCmd = pStorage->m_stkToRedo.top();
  pCmd->ReExecute();
  pStorage->m_stkToRedo.pop();

  pStorage->m_stkToUndo.push(pCmd);  //������һ��ջ��,�ȴ���ִ�г���
}
