#pragma once

#include "CADShape.h"
#include "GYSingleInstanceMacro.h"

#include <stack>
using namespace std;

#include "CADCommand.h"

class CCADStorage
{
public:
  SINGLE_INSTANCE(CCADStorage)

  CList<CCADShape *, CCADShape *> m_lstShapes;  //保存所有的已存在形状

  stack <CADCommand *> m_stkToUndo; //等待撤消的动作
  stack <CADCommand *> m_stkToRedo; //等待重做的动作

private:
  CCADStorage();
  virtual ~CCADStorage();
};

