#include "stdafx.h"
#include "CADShapePencil.h"

IMPLEMENT_SERIAL(CCADShapePencil, CObject, 1)

CCADShapePencil::CCADShapePencil()
{
  m_bIsSavable = true;
}


CCADShapePencil::~CCADShapePencil()
{
}

int CCADShapePencil::SetEndPoint(CPoint & objEndPoint)
{
  CCADShape::SetEndPoint(objEndPoint);

  m_lstPencilPoints.AddTail(objEndPoint);

  return 0;
}

CDC * CCADShapePencil::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);

  //铅笔画
  CPen pen(m_nPenStyle, m_nPenWidth, m_nPenColor);
  CPen *pPenOld = pMemDC->SelectObject(&pen);

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

  pMemDC->MoveTo(m_objBeginPoint);
  POSITION posSelected = m_lstPencilPoints.GetHeadPosition();
  while (posSelected)
  {
    CPoint tmpPoint = m_lstPencilPoints.GetNext(posSelected);
    pMemDC->LineTo(tmpPoint);
    pMemDC->MoveTo(tmpPoint);
  }

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

  //如果不是画背景的话，就把自己
  if (m_bIsDrawingBackground == false)
  {
    CRect rcClient;
    GetClientRect(hWnd, &rcClient);
    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
  }

  return 0;
}

void CCADShapePencil::Serialize(CArchive& archive)
{
  // call base class function first
  // base class is CObject in this case
  CCADShape::Serialize(archive);

  // now do the stuff for our specific class
  if (archive.IsStoring())
  {
    int nCount = m_lstPencilPoints.GetCount();
    archive << nCount;

    POSITION posSelected = m_lstPencilPoints.GetHeadPosition();
    while (posSelected)
    {
      CPoint tmpPoint = m_lstPencilPoints.GetNext(posSelected);
      archive << tmpPoint;
    }

  }
  else
  {
    int nCount;
    archive >> nCount;

    CPoint tmpPoint;
    for (int i = 0; i < nCount; i++)
    {
      archive >> tmpPoint;
      m_lstPencilPoints.AddTail(tmpPoint);
    }

  }

}

int CCADShapePencil::WhenDragged(int nCoordXOffset, int nCoordYOffset)
{
  CCADShape::WhenDragged(nCoordXOffset, nCoordYOffset);

  POSITION posSelected = m_lstPencilPoints.GetHeadPosition();
  POSITION posBefore = m_lstPencilPointsBefore.GetHeadPosition();
  while (posSelected)
  {
    m_lstPencilPoints.GetNext(posSelected).x = m_lstPencilPointsBefore.GetNext(posBefore).x + nCoordXOffset;
  }

  posSelected = m_lstPencilPoints.GetHeadPosition();
  posBefore = m_lstPencilPointsBefore.GetHeadPosition();
  while (posSelected)
  {
    m_lstPencilPoints.GetNext(posSelected).y = m_lstPencilPointsBefore.GetNext(posBefore).y + nCoordYOffset;
  }

  return 0;
}

int CCADShapePencil::BeforeBeingDragged()
{
  CCADShape::BeforeBeingDragged();

  m_lstPencilPointsBefore.RemoveAll();

  POSITION posSelected = m_lstPencilPoints.GetHeadPosition();
  while (posSelected)
  {
    m_lstPencilPointsBefore.AddTail(m_lstPencilPoints.GetNext(posSelected));
  }

  return 0;
}