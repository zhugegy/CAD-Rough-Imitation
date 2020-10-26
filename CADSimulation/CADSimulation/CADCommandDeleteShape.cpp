#include "stdafx.h"
#include "CADCommandDeleteShape.h"

#include "CADStorage.h"

void CADCommandDeleteShape::UnExecute()
{
  if (m_pShapeDeleted == NULL)
  {
    return;
  }

  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  pStorage->m_lstShapes.AddTail(m_pShapeDeleted);
}

void CADCommandDeleteShape::ReExecute()
{
  if (m_pShapeDeleted == NULL)
  {
    return;
  }

  CCADStorage* pStorage = GET_SINGLE(CCADStorage);

  POSITION posToDelete = pStorage->m_lstShapes.Find(m_pShapeDeleted);
  if (posToDelete)
  {
    pStorage->m_lstShapes.RemoveAt(posToDelete);
  }
}
