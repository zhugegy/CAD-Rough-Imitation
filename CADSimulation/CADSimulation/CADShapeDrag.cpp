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
  //������
  CPen pen(PS_DASH, 1, RGB(0, 0, 0));
  CPen *pPenOld = pMemDC->SelectObject(&pen);

  CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
  CBrush *pBrushOld = pMemDC->SelectObject(pBrush);

  pMemDC->SelectObject(pPenOld);
  pMemDC->SelectObject(pBrushOld);

  //������ǻ������Ļ����Ͱ��Լ�
  if (m_bIsDrawingBackground == false)
  {
    CRect rcClient;
    GetClientRect(hWnd, &rcClient);
    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
  }

  return 0;
}

int CCADShapeDrag::SetBeginPoint(CPoint & objBeginPoint)
{
  CCADShape::SetBeginPoint(objBeginPoint);

  //������ǰѡ��
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

  //������ǰѡ��
  POSITION posSelected = (theApp.m_lstSelectedShapes).GetHeadPosition();
  while (posSelected)
  {
    CCADShape * pShape = (theApp.m_lstSelectedShapes).GetNext(posSelected);

    pShape->WhenDragged(nCoordXOffset, nCoordYOffset);
  }

  return 0;
}

CCADShape::RealName CCADShapeDrag::RevealActualType()
{
  return SHAPE_TYPE_DRAG;
}
