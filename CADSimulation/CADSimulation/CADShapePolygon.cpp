#include "stdafx.h"
#include "CADShapePolygon.h"

#include "CADDialogDrawCustomizeShape.h"

IMPLEMENT_SERIAL(CCADShapePolygon, CObject, 1)


CCADShapePolygon::CCADShapePolygon()
{
  m_bIsSavable = true;

}


CCADShapePolygon::~CCADShapePolygon()
{
}

CDC * CCADShapePolygon::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);
  //画多边形
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

  TransferPolygonPoints();

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

  //方法A
//   CRgn rgnPolygon;
//   rgnPolygon.CreatePolygonRgn(m_aryTransferedPoints, m_nPointCount, WINDING);
  //BOOL FillRgn( CRgn* pRgn, CBrush* pBrush );

  //方法B
  pMemDC->SetPolyFillMode(WINDING);
  pMemDC->Polygon(m_aryTransferedPoints, m_nPointCount);

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

int CCADShapePolygon::TransferPolygonPoints()
{
  double dblXDistance = (double)(m_objEndPoint.x - m_objBeginPoint.x);
  double dblXRatio = dblXDistance / CUSTOMIZE_SHAPE_MATRIX_WIDTH;
  double dblYDistance = (double)(m_objEndPoint.y - m_objBeginPoint.y);
  double dblYRatio = dblYDistance / CUSTOMIZE_SHAPE_MATRIX_WIDTH;

  for (int i = 0; i < m_nPointCount; i++)
  {
    m_aryTransferedPoints[i].x = (int)(m_objBeginPoint.x + m_aryPoints[i].x * dblXRatio);
    m_aryTransferedPoints[i].y = (int)(m_objBeginPoint.y + m_aryPoints[i].y * dblYRatio);
  }

  return 0;
}


BOOL CCADShapePolygon::IsSelected(LPRECT pUserRect)
{
  CRgn rgnBuffer;
  rgnBuffer.CreatePolygonRgn(m_aryTransferedPoints, m_nPointCount, WINDING);


  return rgnBuffer.RectInRegion(pUserRect);
}

int CCADShapePolygon::WhenDragged(int nCoordXOffset, int nCoordYOffset)
{
  CCADShape::WhenDragged(nCoordXOffset, nCoordYOffset);

  for (int i = 0; i < m_nPointCount; i++)
  {
    m_aryTransferedPoints[i].x = m_aryTransferedPointsBefore[i].x + nCoordXOffset;
    m_aryTransferedPoints[i].y = m_aryTransferedPointsBefore[i].y + nCoordYOffset;
  }

  return 0;
}

int CCADShapePolygon::BeforeBeingDragged()
{
  CCADShape::BeforeBeingDragged();

  for (int i = 0; i < m_nPointCount; i++)
  {
    m_aryTransferedPointsBefore[i].x = m_aryTransferedPoints[i].x;
    m_aryTransferedPointsBefore[i].y = m_aryTransferedPoints[i].y;
  }

  return 0;
}


void CCADShapePolygon::Serialize(CArchive& archive)
{
  // call base class function first
  // base class is CObject in this case
  CCADShape::Serialize(archive);

  // now do the stuff for our specific class
  if (archive.IsStoring())
  {
    archive << m_nPointCount;

    for (int i = 0; i < 10; i++)
    {
      archive << m_aryPoints[i] << m_aryTransferedPoints[i];
    }
  }
  else
  {
    archive >> m_nPointCount;

    for (int i = 0; i < 10; i++)
    {
      archive >> m_aryPoints[i] >> m_aryTransferedPoints[i];
    }
  }
}