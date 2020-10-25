#pragma once
class ICADCommand
{
public:
  virtual void UnExecute() = 0;
  virtual void ReExecute() = 0;
};

