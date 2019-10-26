#ifndef __DROID_H__
#define __DROID_H__

#include <FastPID.h>
#include <LinkedList.h>
#include <SoftwareSerial.h>
#include <UbxGpsNavPvt.h>

#include "Object.h"
#include "Structs.h"

class Droid : public Object
{
protected:
  int _turningRadius = 30;
  int _targetSpeed = 10;
  int _updateInterval = 1000;
  int _controlInterval = 100;
  int _maxWaypoints = 20;
  int _maxComponents = 5;

  double _magneticDeclination = 0.21;
  int _gpsBaudrate = 9600;
  int _gpsRx = 3;
  int _gpsTx = 2;

  int _vdPin = A2;
  double _vdR1 = 47000.0;
  double _vdR2 = 33000.0;
  double _battMin = 10;
  double _battMax = 12.6;

private:
  SoftwareSerial *_ss;
  UbxGpsNavPvt<SoftwareSerial>* _gps;

  int _left;
  int _right;

  FastPID _pidHeading;
  FastPID _pidSpeed;
  DroidData _data;
  uint32_t _lastSend;
  uint32_t _lastUpdate;
  LinkedList<Point *> _waypoints;
  uint16_t _current;
  LinkedList<Component *> _components;

  void FetchData();
  void Control();
  void Ping();

public:
  Droid(int nodeId);
  virtual void Setup();
  virtual void Update();

  void AddComponent(Component *component);
};

#endif
