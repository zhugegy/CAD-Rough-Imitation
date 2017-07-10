#include "stdafx.h"
#include "CADShapeRect.h"


CCADShapeRect::CCADShapeRect()
{
}


CCADShapeRect::~CCADShapeRect()
{
}

CDC * CCADShapeRect::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);
  //画矩形
  CPen pen(m_nPenStyle, m_nPenWidth, m_nPenColor);
  CPen *pPenOld = pMemDC->SelectObject(&pen);

  CBrush *pBrushOld = NULL;
  CBrush brush;
  if (m_nBrushColor == -1)
  {
    CBrush *pBrush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
    pBrushOld = pMemDC->SelectObject(pBrush);
  }
  else
  {
    brush.CreateSolidBrush(m_nBrushColor);
    pBrushOld = pMemDC->SelectObject(&brush);
  }

  POINT centerPt;
  centerPt.x = (m_objBeginPoint.x + m_objEndPoint.x) / 2;
  centerPt.y = (m_objBeginPoint.y + m_objEndPoint.y) / 2;

  int nGraphicsMode = SetGraphicsMode(pMemDC->m_hDC, GM_ADVANCED);
  XFORM xform;
  if (m_nRotation != 0)
  {
    double fangle = (double)m_nRotation / 180. * 3.1415926;
    xform.eM11 = (float)cos(fangle);
    xform.eM12 = (float)sin(fangle);
    xform.eM21 = (float)-sin(fangle);
    xform.eM22 = (float)cos(fangle);
    xform.eDx = (float)(centerPt.x - cos(fangle)*centerPt.x + sin(fangle)*centerPt.y);
    xform.eDy = (float)(centerPt.y - cos(fangle)*centerPt.y - sin(fangle)*centerPt.x);

    SetWorldTransform(pMemDC->m_hDC, &xform);
  }

  pMemDC->Rectangle(m_objBeginPoint.x, m_objBeginPoint.y,
    m_objEndPoint.x, m_objEndPoint.y);
//   CBrush brush;
//   brush.CreateSolidBrush(m_nBrushColor);
//   pBrushOld = pMemDC->SelectObject(&brush);
//   pMemDC->FillRect(CRect(m_objBeginPoint, m_objEndPoint), &brush);

  if (m_nRotation != 0)
  {
    xform.eM11 = (float)1.0;
    xform.eM12 = (float)0;
    xform.eM21 = (float)0;
    xform.eM22 = (float)1.0;
    xform.eDx = (float)0;
    xform.eDy = (float)0;

    SetWorldTransform(pMemDC->m_hDC, &xform);
  }
  SetGraphicsMode(pMemDC->m_hDC, nGraphicsMode);

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