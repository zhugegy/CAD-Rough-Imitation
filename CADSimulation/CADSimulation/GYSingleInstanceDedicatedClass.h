#pragma once

#include "GYSingleInstanceMacro.h"

//此类配合单例模式使用（用于在main()函数发生之前构造单例对象）。编程过程中没必要使用。

class CGYSingleInstanceDedicatedClass
{
public:
	CGYSingleInstanceDedicatedClass();
	virtual ~CGYSingleInstanceDedicatedClass();
};

