#include "SteeringServo.h"
#include <Arduino.h>

SteeringServo::SteeringServo(int pin)
{
  _pin = pin;
  _servo.attach(pin);
}

void SteeringServo::Update(int *left, int *right, DroidData *data)
{
  Component::Update(left, right, data);
  _servo.write(map(*left - *right, -100, 100, 0, 180));
}
