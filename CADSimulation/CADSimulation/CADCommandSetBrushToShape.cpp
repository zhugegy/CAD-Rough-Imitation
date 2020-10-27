#include "stdafx.h"
#include "CADCommandSetBrushToShape.h"

void CADCommandSetBrushToShape::UnExecute()
{
  if (m_pShapeSetBrushTo == NULL)
  {
    return;
  }

  m_pShapeSetBrushTo->SetBrushCommand(m_nBrushColorBefore);
}

void CADCommandSetBrushToShape::ReExecute()
{
  if (m_pShapeSetBrushTo == NULL)
  {
    return;
  }

  m_pShapeSetBrushTo->SetBrushCommand(m_nBrushColorAfter);
}
