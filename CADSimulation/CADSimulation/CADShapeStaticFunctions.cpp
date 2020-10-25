#include "stdafx.h"

#include "CADShapeStaticFunctions.h"
#include "CADSimulation.h"

#include "CADStorage.h"
#include "ICADCommand.h"

#include <afxwin2.inl>

int CCADShapeStaticFunctions::delete_shapes()
{
  //������ǰѡ��
  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape* pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);
    pStorage->m_lstShapes.RemoveAt(pStorage->m_lstShapes.Find(pShape));
    delete pShape;
    pShape = NULL;
  }

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
