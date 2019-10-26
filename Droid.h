#ifndef __DROID_H__
#define __DROID_H__

#include <FastPID.h>

#include "Object.h"
#include "Structs.h"
#include "Components.h"

class Droid : public Object
{
private:
  int _left;
  int _right;

  FastPID _pidHeading;
  FastPID _pidSpeed;
  DroidData _data;
  uint32_t _lastSend;
  uint32_t _lastUpdate;
  Point *_waypoints[MAX_WAYPOINTS];
  uint16_t _current;
  Component *_components[MAX_COMPONENTS];

  void FetchData();
  void Control();
  void Ping();

public:
  virtual void Setup();
  virtual void Update();

  void AddComponent(Component *component);
};

#endif
