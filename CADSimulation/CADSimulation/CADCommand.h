#pragma once
class CADCommand
{
public:
  virtual void UnExecute() = 0;
  virtual void ReExecute() = 0;
};

