#ifndef __ULTRASONIC_SENSOR_H__
#define __ULTRASONIC_SENSOR_H__

#include "Component.h"

class UltrasonicSensor : public Component
{
private:
    int _trig;
    int _echo;
    int _side;
    int _threshold;
    int _strength;

public:
    UltrasonicSensor(int trig, int echo, int side, int threshold, int strength);
    void Update(int *left, int *right, DroidData *data);
};
#endif