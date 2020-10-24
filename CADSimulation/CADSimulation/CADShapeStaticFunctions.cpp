#include "stdafx.h"

#include "CADShapeStaticFunctions.h"
#include "CADSimulation.h"

#include "CADStorage.h"

#include <afxwin2.inl>

int CCADShapeStaticFunctions::delete_shapes()
{
  // AfxMessageBox("new imp");
  //遍历当前选择
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
