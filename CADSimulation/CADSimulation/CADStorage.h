#pragma once

#include "CADShape.h"
#include "GYSingleInstanceMacro.h"

class CCADStorage
{
public:
  SINGLE_INSTANCE(CCADStorage)

  CList<CCADShape *, CCADShape *> m_lstShapes;  //保存所有的已存在形状

private:
  CCADStorage();
  virtual ~CCADStorage();
};

