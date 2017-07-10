#include "stdafx.h"
#include "CADShapeSelection.h"

#include "CADStorage.h"
#include "CADSimulation.h"
#include "CADSimulationView.h"


CCADShapeSelection::CCADShapeSelection()
{
  m_bIsSelectionDone = false;
}


CCADShapeSelection::~CCADShapeSelection()
{
}

CDC * CCADShapeSelection::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);
  //画矩形
  CPen pen(PS_DASH, 1, RGB(0, 0, 0));
  CPen *pPenOld = pMemDC->SelectObject(&pen);

  CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
  CBrush *pBrushOld = pMemDC->SelectObject(pBrush);

  if (m_bIsSelectionDone == false)
  {
    pMemDC->Rectangle(m_objBeginPoint.x, m_objBeginPoint.y,
      m_objEndPoint.x, m_objEndPoint.y);
  }

  pMemDC->SelectObject(pPenOld);
  pMemDC->SelectObject(pBrushOld);

  //如果不是画背景的话，就把自己
  if (m_bIsDrawingBackground == false)
  {
    CRect rcClient;
    GetClientRect(hWnd, &rcClient);
    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
  }

  return 0;
}

int CCADShapeSelection::SaveThisShape(CPoint & objPoint)
{
  //不保存此图形，而是进行其他事情（寻找被用户拿出的图形）
  FindSelectedShapes();

  return 0;
}

extern CCADSimulationApp theApp;

int CCADShapeSelection::FindSelectedShapes()
{
  //遍历链表,绘制每一个保存的图形
  CCADStorage *pStorage = GET_SINGLE(CCADStorage);

  POSITION pos = (pStorage->m_lstShapes).GetHeadPosition();
  while (pos)
  {
    CCADShape * pShape = (pStorage->m_lstShapes).GetNext(pos);

    if (pShape->IsSelected(&CRect(m_objBeginPoint, m_objEndPoint)) == TRUE)
    {
      theApp.m_lstSelectedShapes.AddTail(pShape);
      pShape->WhenSelected();
    }
  }

  m_bIsSelectionDone = true;

  return 0;
}
