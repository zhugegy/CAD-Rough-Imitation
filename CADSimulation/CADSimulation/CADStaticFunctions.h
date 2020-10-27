#pragma once
#include "CADShape.h"
class CADStaticFunctions :
  public CCADShape
{
public:
  static int delete_shapes();

  static int unselect_all();

  static void Undo();
  static void Redo();

};

