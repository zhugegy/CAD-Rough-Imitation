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

  CList<CCADShape *, CCADShape *> m_lstShapes;  //�������е��Ѵ�����״

  stack <CADCommand *> m_stkToUndo; //�ȴ������Ķ���
  stack <CADCommand *> m_stkToRedo; //�ȴ������Ķ���

private:
  CCADStorage();
  virtual ~CCADStorage();
};

