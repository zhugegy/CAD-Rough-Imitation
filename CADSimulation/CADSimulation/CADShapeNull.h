#pragma once
#include "CADShape.h"

/* �����ʲô�������������趨һЩ���⹦�ܵ�Context�����糷����������ʱ��
�Ͳ�Ӧ����Context��CurrentShape���������һ�����Ρ�ֱ��Ȼ��ʱ�������ǣ�
����Ӧ��ʲô�����ͼ�ζ���������*/
class CCADShapeNull :
    public CCADShape
{
public:
  CCADShapeNull();
  virtual ~CCADShapeNull();
};

