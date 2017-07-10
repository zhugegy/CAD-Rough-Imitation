#include "stdafx.h"
#include "CADShapeLine.h"

IMPLEMENT_SERIAL(CCADShapeLine, CObject, 1)


CCADShapeLine::CCADShapeLine()
{
  m_bIsSavable = true;
}


CCADShapeLine::~CCADShapeLine()
{
}

CDC * CCADShapeLine::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);

  //画直线
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
  pMemDC->LineTo(m_objEndPoint);

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
/*
       0----------->X
       |
       |
       |
       |
       |
       Y

  case A: Bx <= Ex && By <= Ey

  BeginPoint
       -
        -
         -
          -
           -
            -
             -
             EndPoint


  case B: Bx >= Ex && By >= Ey

  EndPoint
       -
        -
         -
          -
           -
            -
             -
             BeginPoint

  case C: Bx <= Ex && By >= Ey
                         
                  EndPoint
                -
               -
              -
             -
            -
           -
        BeginPoint

  case D: Bx >= Ex && By <= Ey

                BeginPoint
               -
              -
             -
            -
           -
          -
         -
     EndPoint
*/

BOOL CCADShapeLine::IsSelected(LPRECT pUserRect)
{
  POINT rgnPoints[4];
  int nThreashhold = 5;

  if (m_objBeginPoint.x <= m_objEndPoint.x && 
    m_objBeginPoint.y <= m_objEndPoint.y)  //case A
  {
    rgnPoints[0].x = m_objBeginPoint.x + nThreashhold;
    rgnPoints[0].y = m_objBeginPoint.y - nThreashhold;

    rgnPoints[1].x = m_objEndPoint.x + nThreashhold;
    rgnPoints[1].y = m_objEndPoint.y - nThreashhold;

    rgnPoints[2].x = m_objEndPoint.x - nThreashhold;
    rgnPoints[2].y = m_objEndPoint.y + nThreashhold;

    rgnPoints[3].x = m_objBeginPoint.x - nThreashhold;
    rgnPoints[3].y = m_objBeginPoint.y + nThreashhold;
  }
  else if (m_objBeginPoint.x >= m_objEndPoint.x &&
    m_objBeginPoint.y >= m_objEndPoint.y)  //case B 同A
  {
    rgnPoints[0].x = m_objBeginPoint.x + nThreashhold;
    rgnPoints[0].y = m_objBeginPoint.y - nThreashhold;

    rgnPoints[1].x = m_objEndPoint.x + nThreashhold;
    rgnPoints[1].y = m_objEndPoint.y - nThreashhold;

    rgnPoints[2].x = m_objEndPoint.x - nThreashhold;
    rgnPoints[2].y = m_objEndPoint.y + nThreashhold;

    rgnPoints[3].x = m_objBeginPoint.x - nThreashhold;
    rgnPoints[3].y = m_objBeginPoint.y + nThreashhold;
  }
  else if (m_objBeginPoint.x <= m_objEndPoint.x &&
    m_objBeginPoint.y >= m_objEndPoint.y)  //case C
  {
    rgnPoints[0].x = m_objBeginPoint.x + nThreashhold;
    rgnPoints[0].y = m_objBeginPoint.y + nThreashhold;

    rgnPoints[1].x = m_objEndPoint.x + nThreashhold;
    rgnPoints[1].y = m_objEndPoint.y + nThreashhold;

    rgnPoints[2].x = m_objEndPoint.x - nThreashhold;
    rgnPoints[2].y = m_objEndPoint.y - nThreashhold;

    rgnPoints[3].x = m_objBeginPoint.x - nThreashhold;
    rgnPoints[3].y = m_objBeginPoint.y - nThreashhold;
  }
  else  //case D(m_objBeginPoint.x >= m_objEndPoint.x && m_objBeginPoint.y <= m_objEndPoint.y) 同C
  {
    rgnPoints[0].x = m_objBeginPoint.x + nThreashhold;
    rgnPoints[0].y = m_objBeginPoint.y + nThreashhold;

    rgnPoints[1].x = m_objEndPoint.x + nThreashhold;
    rgnPoints[1].y = m_objEndPoint.y + nThreashhold;

    rgnPoints[2].x = m_objEndPoint.x - nThreashhold;
    rgnPoints[2].y = m_objEndPoint.y - nThreashhold;

    rgnPoints[3].x = m_objBeginPoint.x - nThreashhold;
    rgnPoints[3].y = m_objBeginPoint.y - nThreashhold;
  }

  //处理所有points，不能越界
  for (int i = 0; i < 4; i++)
  {
    if (rgnPoints[i].x < 0)
    {
      rgnPoints[i].x = 0;
    }

    if (rgnPoints[i].y < 0)
    {
      rgnPoints[i].y = 0;
    }
  }

  CRgn rgnBuffer;
  rgnBuffer.CreatePolygonRgn(rgnPoints, 4, WINDING);

  return rgnBuffer.RectInRegion(pUserRect);
}

void CCADShapeLine::Serialize(CArchive& archive)
{
  // call base class function first
  // base class is CObject in this case
  CCADShape::Serialize(archive);

  // now do the stuff for our specific class
  if (archive.IsStoring())
  {

  }
  else
  {

  }
}