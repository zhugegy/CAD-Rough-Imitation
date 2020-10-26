#include "stdafx.h"

#include "CADShapeStaticFunctions.h"
#include "CADSimulation.h"

#include "CADStorage.h"
#include "ICADCommand.h"
#include "CADCommandDeleteShapes.h"
#include "CADCommandDeleteShape.h"

#include <afxwin2.inl>

int CCADShapeStaticFunctions::delete_shapes()
{
  //������ǰѡ��
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();

  if (posSelected == NULL)
  {
    return -1;
  }

  CADCommandDeleteShapes* pCmdDeleteShapes = new CADCommandDeleteShapes;

  while (posSelected)
  {
    CCADShape* pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    POSITION posToDelete = pStorage->m_lstShapes.Find(pShape);
    if (posToDelete)
    {
      pStorage->m_lstShapes.RemoveAt(posToDelete);

      CADCommandDeleteShape* pCmdDeleteShape = new CADCommandDeleteShape;
      pCmdDeleteShape->m_pShapeDeleted = pShape;
      pCmdDeleteShapes->PushDeleteShapeCommand(pCmdDeleteShape);
    }
  }

  ASSERT(pCmdDeleteShapes->GetCommandCount() != 0);

  if (pCmdDeleteShapes->GetCommandCount())
  {
    pStorage->m_stkToUndo.push(pCmdDeleteShapes);
  }

  return 0;
}

int CCADShapeStaticFunctions::unselect_all()
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

void CCADShapeStaticFunctions::Undo()
{
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  if (pStorage->m_stkToUndo.empty())
  {
    return;
  }

  //����
  ICADCommand* pCmd = pStorage->m_stkToUndo.top();
  pCmd->UnExecute(); 
  pStorage->m_stkToUndo.pop();

  pStorage->m_stkToRedo.push(pCmd);  //������һ��ջ��,�ȴ���ִ������
}

void CCADShapeStaticFunctions::Redo()
{
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  //ջΪ��, ˵��û�в�����Ҫ������
  if (pStorage->m_stkToRedo.empty())
  {
    return;
  }

  //����
  ICADCommand* pCmd = pStorage->m_stkToRedo.top();
  pCmd->ReExecute();
  pStorage->m_stkToRedo.pop();

  pStorage->m_stkToUndo.push(pCmd);  //������һ��ջ��,�ȴ���ִ�г���
}
