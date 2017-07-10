#include "stdafx.h"
#include "CADShapeDrag.h"
#include "CADSimulation.h"


CCADShapeDrag::CCADShapeDrag()
{
}


CCADShapeDrag::~CCADShapeDrag()
{
}

extern CCADSimulationApp theApp;

CDC * CCADShapeDrag::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);
  //画矩形
  CPen pen(PS_DASH, 1, RGB(0, 0, 0));
  CPen *pPenOld = pMemDC->SelectObject(&pen);

  CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
  CBrush *pBrushOld = pMemDC->SelectObject(pBrush);

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

int CCADShapeDrag::SaveThisShape(CPoint & objPoint)
{
  //不保存此图形

  return 0;
}

int CCADShapeDrag::SetBeginPoint(CPoint & objBeginPoint)
{
  CCADShape::SetBeginPoint(objBeginPoint);

  //遍历当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->BeforeBeingDragged();
  }

  return 0;
}

int CCADShapeDrag::SetEndPoint(CPoint & objBeginPoint)
{
  CCADShape::SetEndPoint(objBeginPoint);

  int nCoordXOffset = m_objEndPoint.x - m_objBeginPoint.x;
  int nCoordYOffset = m_objEndPoint.y - m_objBeginPoint.y;

  //遍历当前选择
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->WhenDragged(nCoordXOffset, nCoordYOffset);
  }

  return 0;
}