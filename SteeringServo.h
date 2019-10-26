#ifndef __STEERING_SERVO_H__
#define __STEERING_SERVO_H__

#include "Component.h"
#include <Servo.h>

class SteeringServo : public Component
{
private:
  int _pin;
  Servo _servo;

public:
  SteeringServo(int pin);
  void Update(int left, int right, DroidData *data);
};
#endif
