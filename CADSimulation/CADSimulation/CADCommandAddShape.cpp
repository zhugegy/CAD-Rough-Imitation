#include "stdafx.h"
#include "CADCommandAddShape.h"

#include "CADSimulation.h"
#include "CADStorage.h"


void CADCommandAddShape::UnExecute()
{
  if (m_pShapeAdded == NULL)
  {
    return;
  }

  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  pStorage->m_lstShapes.RemoveAt(pStorage->m_lstShapes.Find(m_pShapeAdded));
  /*delete m_pShapeAdded;
  m_pShapeAdded = NULL;*/
}

void CADCommandAddShape::ReExecute()
{
  if (m_pShapeAdded == NULL)
  {
    return;
  }

  CCADStorage* pStorage = GET_SINGLE(CCADStorage);
  pStorage->m_lstShapes.AddTail(m_pShapeAdded);
}
