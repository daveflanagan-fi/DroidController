#ifndef __MASTER_H__
#define __MASTER_H__

#include "Object.h"
#include "Structs.h"

class MasterNode : public Object
{
private:
  uint32_t _lastList;

public:
  MasterNode();
  virtual void Update();
};

#endif
