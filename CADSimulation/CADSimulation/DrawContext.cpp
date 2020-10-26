#include "stdafx.h"
#include "DrawContext.h"

#include "CADShapePencil.h"
#include "CADShapeLine.h"
#include "CADShapeRect.h"
#include "CADShapeEllipse.h"
#include "CADShapePolygon.h"
#include "CADShapeSelection.h"
#include "CADShapeDrag.h"
#include "CADSimulation.h"
#include "CADShapeNull.h"

extern CCADSimulationApp theApp;

CDrawContext::CDrawContext()
{
  m_pobjCurrentShape = new CCADShape;
  //m_pobjCurrentShape = new CCADShapeLine;

}

CDrawContext::CDrawContext(CString &strShapeName)
{
//   if (m_pobjCurrentShape != NULL)
//   {
//     delete m_pobjCurrentShape;
//     m_pobjCurrentShape = NULL;
//   }
// 
//   SetShape(strShapeName);
}

CDrawContext::~CDrawContext()
{
//   if (m_pobjCurrentShape != NULL)
//   {
//     delete m_pobjCurrentShape;
//     m_pobjCurrentShape = NULL;
//   }
}


int CDrawContext::SetShapeContext()
{
  if (*(theApp.GetLastShapeName()) == _T("铅笔"))
  {
    m_pobjCurrentShape = new CCADShapePencil;
  }

  if (*(theApp.GetLastShapeName()) == _T("直线"))
  {
    m_pobjCurrentShape = new CCADShapeLine;
  }

  if (*(theApp.GetLastShapeName()) == _T("矩形"))
  {
    m_pobjCurrentShape = new CCADShapeRect;
  }

  if (*(theApp.GetLastShapeName()) == _T("椭圆"))
  {
    m_pobjCurrentShape = new CCADShapeEllipse;
  }

  if (*(theApp.GetLastShapeName()) == _T("自定义图形") && 
    theApp.m_nCustomiezedShapePointCount >= 3)
  {
    m_pobjCurrentShape = new CCADShapePolygon;

    memcpy(((CCADShapePolygon *)m_pobjCurrentShape)->m_aryPoints,
      theApp.m_aryCustomizedShapePoints,
      sizeof(((CCADShapePolygon *)m_pobjCurrentShape)->m_aryPoints));

    ((CCADShapePolygon *)m_pobjCurrentShape)->m_nPointCount = 
      theApp.m_nCustomiezedShapePointCount;
  }

  if (*(theApp.GetLastShapeName()) == _T("选择"))
  {
    m_pobjCurrentShape = new CCADShapeSelection;
  }

  if (*(theApp.GetLastShapeName()) == _T("取消"))
  {
    //m_pobjCurrentShape = new CCADShapeLine;
    //m_pobjCurrentShape = new CCADShape;
    m_pobjCurrentShape = new CCADShapeNull;
  }

  if (*(theApp.GetLastShapeName()) == _T("拖动"))
  {
    m_pobjCurrentShape = new CCADShapeDrag;
  }


  return 0;
}

CCADShape* CDrawContext::GetShapeContext()
{
  return m_pobjCurrentShape;
}

int CDrawContext::TemporarilyNullCurrentShapeContext()
{
  m_pobjCurrentShape = new CCADShapeNull;

  return 0;
}

int CDrawContext::RestorePreviousShapeContext(CCADShape* pPrevious)
{
  m_pobjCurrentShape = pPrevious;

  return 0;
}

int CDrawContext::OnLButtonDown(CPoint & objPoint)
{
  SetShapeContext();
  m_pobjCurrentShape->SetBeginPoint(objPoint);

  return 0;
}

int CDrawContext::OnMouseMove(CPoint & objPoint)
{
  m_pobjCurrentShape->SetEndPoint(objPoint);

  return 0;
}

int CDrawContext::OnLButtonUp(CPoint & objPoint)
{
  m_pobjCurrentShape->SetEndPoint(objPoint);
  m_pobjCurrentShape->SaveThisShape(objPoint);

  

  return 0;
}

int CDrawContext::Draw(HWND hWnd, CDC * pDC)
{
  m_pobjCurrentShape->DrawTheBigPicture(hWnd, pDC);

  return 0;
}

