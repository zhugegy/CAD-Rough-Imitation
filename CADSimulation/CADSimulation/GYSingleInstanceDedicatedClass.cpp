#include "stdafx.h"
#include "GYSingleInstanceDedicatedClass.h"
#include "CADStorage.h"

CGYSingleInstanceDedicatedClass::CGYSingleInstanceDedicatedClass()
{
	CREATE_SINGLE(CCADStorage)
}


CGYSingleInstanceDedicatedClass::~CGYSingleInstanceDedicatedClass()
{
	RELEASE_SINGLE(CCADStorage)
}
