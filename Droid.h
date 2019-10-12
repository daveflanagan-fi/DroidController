#ifndef __DROID_H__
#define __DROID_H__

#include <FastPID.h>

#include "Object.h"
#include "Structs.h"
#include "Config.h"

class Motor {
  private:
    int _in1;
    int _in2;
    int _en;
  public:
    void Setup(int in1, int in2, int en);
    void Set(int speed, boolean reverse);
};

class Droid : public Object {
  private:
    int _left;
    int _right;
    
    FastPID _pidHeading;
    FastPID _pidSpeed;
    DroidData _data;
    uint32_t _lastSend;
    uint32_t _lastUpdate;
    Point* _waypoints[MAX_WAYPOINTS];
    uint16_t _current;
    Accessory* _accessories[MAX_ACCESSORIES];

    Motor _leftMotor;
    Motor _rightMotor;

    void FetchData();
    void Control();
    void Ping();
    
  public:
    virtual void Setup();
    virtual void Update();

    void AddAccessory(Accessory* accessory);
};

#endif
