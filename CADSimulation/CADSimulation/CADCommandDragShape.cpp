#include "stdafx.h"
#include "CADCommandDragShape.h"

void CADCommandDragShape::UnExecute()
{
  if (m_pShapeDragged == NULL)
  {
    return;
  }

  m_pShapeDragged->WhenUndraggedCommandMode(m_ptStartPTBeforeDragged, m_ptEndPTBeforeDragged);
}

void CADCommandDragShape::ReExecute()
{
  if (m_pShapeDragged == NULL)
  {
    return;
  }

  m_pShapeDragged->WhenDraggedCommandMode(m_nCoordXOffset, m_nCoordYOffset);
}

void CADCommandDragShape::SetOriginPoint(CPoint& ptStartPTBeforeDragged, 
  CPoint& ptEndPTBeforeDragged)
{
  m_ptStartPTBeforeDragged = ptStartPTBeforeDragged;
  m_ptEndPTBeforeDragged = ptEndPTBeforeDragged;
}

void CADCommandDragShape::SetOffsets(int x, int y)
{
  m_nCoordXOffset = x;
  m_nCoordYOffset = y;
}
