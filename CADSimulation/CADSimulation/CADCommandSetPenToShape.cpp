#include "stdafx.h"
#include "CADCommandSetPenToShape.h"

void CADCommandSetPenToShape::UnExecute()
{
  if (m_pShapeSetPenTo == NULL)
  {
    return;
  }

  m_pShapeSetPenTo->SetPen(m_nPenWidthBefore, m_nPenStyleBefore, m_nPenColorBefore);
}

void CADCommandSetPenToShape::ReExecute()
{
  if (m_pShapeSetPenTo == NULL)
  {
    return;
  }

  m_pShapeSetPenTo->SetPen(m_nPenWidthAfter, m_nPenStyleAfter, m_nPenColorAfter);
}
