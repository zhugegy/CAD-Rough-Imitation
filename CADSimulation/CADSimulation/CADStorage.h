#pragma once

#include "CADShape.h"
#include "GYSingleInstanceMacro.h"

#include <stack>
using namespace std;

#include "ICADCommand.h"

class CCADStorage
{
public:
  SINGLE_INSTANCE(CCADStorage)

  CList<CCADShape *, CCADShape *> m_lstShapes;  //�������е��Ѵ�����״

  stack <ICADCommand *> m_stkToUndo; //�ȴ������Ķ���
  stack <ICADCommand *> m_stkToRedo; //�ȴ������Ķ���

private:
  CCADStorage();
  virtual ~CCADStorage();
};

