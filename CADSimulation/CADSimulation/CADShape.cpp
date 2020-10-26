#include "stdafx.h"
#include "CADShape.h"
#include "CADStorage.h"
#include "GYSingleInstanceMacro.h"
#include "CADSimulation.h"
#include "CADCommandAddShape.h"

extern CCADSimulationApp theApp;

CDC * CCADShape::m_pStaticDCMem = NULL;
CBitmap * CCADShape::m_pStaticBitmap = NULL;
bool CCADShape::m_bIsDrawingBackground = false;

CCADShape::CCADShape()
{
  //==负责收集new出来的对象
  //m_bIsStyleSet = false;
  m_nPenWidth = theApp.m_nPenWidth;
  m_nPenStyle = theApp.m_nPenStyle;
  m_nPenColor = theApp.m_nPenColor;
  m_nBrushColor = theApp.m_nBrushColor;

  m_nPenWidthSwitch = theApp.m_nPenWidth;
  m_nPenStyleSwitch = theApp.m_nPenStyle;
  m_nPenColorSwitch = theApp.m_nPenColor;
  m_nBrushColorSwitch = theApp.m_nBrushColor;

  m_nRotation = 0;

  m_bIsSavable = false;
}


CCADShape::~CCADShape()
{
}


int CCADShape::SetBeginPoint(CPoint & objBeginPoint)
{
  m_objBeginPoint = objBeginPoint;

  return 0;
}


int CCADShape::SetEndPoint(CPoint & objEndPoint)
{
  m_objEndPoint = objEndPoint;

  return 0;
}


CDC * CCADShape::Draw(HWND hWnd, CDC * pDC)
{
  CDC *pMemDC = GetMemDC(hWnd, pDC);

  //如果不是画背景的话，就把自己
  if (m_bIsDrawingBackground == false)
  {
    CRect rcClient;
    GetClientRect(hWnd, &rcClient);
    pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), pMemDC, 0, 0, SRCCOPY);
  }

  return NULL;
}

int CCADShape::SaveThisShape(CPoint & objPoint)
{
  if (m_bIsSavable == true)
  {
    CCADStorage *pStorage = GET_SINGLE(CCADStorage);

    (pStorage->m_lstShapes).AddTail(this);

    CADCommandAddShape* pCmd = new CADCommandAddShape;
    pCmd->m_pShapeAdded = this;
    pStorage->m_stkToUndo.push(pCmd);
  }
  else
  {
    if (this->RevealActualType() == SHAPE_TYPE_DRAG)
    {
      
    }
  }

  return 0;
}


CDC * CCADShape::GetMemDC(HWND hWnd, CDC * pDC)
{
  CRect rc;
  GetClientRect(hWnd, &rc);

  if (m_pStaticDCMem == NULL)
  {
    //创建一个兼容DC(内存DC)
    m_pStaticDCMem = new CDC;
    m_pStaticDCMem->CreateCompatibleDC(pDC);

    //创建兼容位图
    m_pStaticBitmap = new CBitmap;
    m_pStaticBitmap->CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

    //将位图放入内存DC
    m_pStaticDCMem->SelectObject(*m_pStaticBitmap);
  }

  return m_pStaticDCMem;
}


int CCADShape::DrawTheBigPicture(HWND hWnd, CDC * pDC)
{
  m_bIsDrawingBackground = true;
  //4.绘图
  ResetMemDCBackground(hWnd, pDC);

  //遍历链表,绘制每一个保存的图形
  CCADStorage *pStorage = GET_SINGLE(CCADStorage);

  POSITION pos = (pStorage->m_lstShapes).GetHeadPosition();
  while (pos)
  {
    CCADShape * pShape = (pStorage->m_lstShapes).GetNext(pos);
    //绘制
    pShape->Draw(hWnd, pDC);
  }

  m_bIsDrawingBackground = false;

  this->Draw(hWnd, pDC);

  return 0;
}


int CCADShape::ResetMemDCBackground(HWND hWnd, CDC * pDC)
{
  CRect rc;
  GetClientRect(hWnd, &rc);

  GetMemDC(hWnd, pDC);

  //将DC清空（空白）
  m_pStaticDCMem->FillSolidRect(&rc, pDC->GetBkColor());

  return 0;
}


BOOL CCADShape::IsSelected(LPRECT pUserRect)
{
  CRgn rgnBuffer;
  rgnBuffer.CreateRectRgnIndirect(&CRect(m_objBeginPoint, m_objEndPoint));


  return rgnBuffer.RectInRegion(pUserRect);
}


int CCADShape::WhenSelected()
{
  m_nPenWidth = 1;
  m_nPenStyle = PS_DASH;
  m_nPenColor = RGB(255, 0, 0);
  m_nBrushColor = RGB(255, 0, 0);

  return 0;
}


int CCADShape::WhenUnselected()
{
  m_nPenWidth = m_nPenWidthSwitch;
  m_nPenStyle = m_nPenStyleSwitch;
  m_nPenColor = m_nPenColorSwitch;
  m_nBrushColor = m_nBrushColorSwitch;

  return 0;
}


int CCADShape::WhenDragged(int nCoordXOffset, int nCoordYOffset)
{
  m_objBeginPoint.x = m_objBeginPointBefore.x + nCoordXOffset;
  m_objEndPoint.x = m_objEndPointBefore.x + nCoordXOffset;

  m_objBeginPoint.y = m_objBeginPointBefore.y + nCoordYOffset;
  m_objEndPoint.y = m_objEndPointBefore.y + nCoordYOffset;

  return 0;
}


int CCADShape::BeforeBeingDragged()
{
  m_objBeginPointBefore = m_objBeginPoint;
  m_objEndPointBefore = m_objEndPoint;

  return 0;
}


int CCADShape::AfterBeingDragged()
{
  //空

  return 0;
}


int CCADShape::SetBrush(COLORREF color)
{
  //直接修改保存的值，不用修改m_nBrushColor，因为等会就会switch回来
  m_nBrushColorSwitch = color;  

  return 0;
}


int CCADShape::SetPen(int PenWidth, int PenStyle, COLORREF PenColor)
{
  //直接修改保存的值，不用修改m_nBrushColor，因为等会就会switch回来
  m_nPenWidthSwitch = PenWidth;
  m_nPenStyleSwitch = PenStyle;
  m_nPenColorSwitch = PenColor;

  return 0;
}


int CCADShape::SetRotation(int nRotation)
{
  m_nRotation = nRotation;

  return 0;
}

void CCADShape::Serialize(CArchive& archive)
{
  // call base class function first
  // base class is CObject in this case
  CObject::Serialize(archive);

  // now do the stuff for our specific class
  if (archive.IsStoring())
  {
    archive << m_objBeginPoint << m_objEndPoint << m_nRotation << m_nPenWidth
      << m_nPenStyle << m_nPenColor << m_nBrushColor;
  }
  else
  {
    archive >> m_objBeginPoint >> m_objEndPoint >> m_nRotation >> m_nPenWidth
      >> m_nPenStyle >> m_nPenColor >> m_nBrushColor;
  }
}

CCADShape::RealName CCADShape::RevealActualType()
{
  return SHAPE_TYPE_DEFAULT;
}
