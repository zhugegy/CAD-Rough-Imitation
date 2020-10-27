#include "stdafx.h"
#include "CADCommandRotateShape.h"

void CADCommandRotateShape::UnExecute()
{
  if (m_pShapeRotated == NULL)
  {
    return;
  }

  m_pShapeRotated->SetRotation(m_nRotationDegreeBefore);
}

void CADCommandRotateShape::ReExecute()
{
  if (m_pShapeRotated == NULL)
  {
    return;
  }

  m_pShapeRotated->SetRotation(m_nRotationDegreeAfter);
}
