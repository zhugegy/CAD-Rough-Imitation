#pragma once
#include "CADShape.h"

/* 这个类什么都不做，用于设定一些特殊功能的Context，例如撤销、重做的时候，
就不应该在Context的CurrentShape里继续保存一个矩形、直线然后即时画出它们，
而是应该什么额外的图形都不画出。*/
class CCADShapeNull :
    public CCADShape
{
public:
  CCADShapeNull();
  virtual ~CCADShapeNull();
};

