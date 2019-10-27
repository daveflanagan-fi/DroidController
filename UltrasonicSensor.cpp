#include "UltrasonicSensor.h"
#include <Arduino.h>

UltrasonicSensor::UltrasonicSensor(int trig, int echo, int side, int threshold, int strength)
{
    _trig = trig;
    _echo = echo;
    _side = side;
    _threshold = threshold;
    _strength = strength;

    pinMode(_trig, OUTPUT);
    pinMode(_echo, INPUT);
}

void UltrasonicSensor::Update(int *left, int *right, DroidData *data)
{
    Component::Update(left, right, data);

    digitalWrite(_trig, LOW);
    delayMicroseconds(2);

    digitalWrite(_trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trig, LOW);

    long duration = pulseIn(_echo, HIGH);
    int distance = duration * 0.034 / 2;
    if (distance < _threshold)
    {
        switch (_side)
        {
        case FRONT:
            // If droid is heading toward obsticle
            if (left > 0 && right > 0)
            {
                // If droid is turning more to left than right
                // Turn hard left else turn hard right
                if (left > right)
                {
                    left += _strength;
                    right -= _strength;
                }
                else
                {
                    left -= _strength;
                    right += _strength;
                }
            }
            break;
        case RIGHT:
            // If turning into obsticle, turn left
            if (left > right)
                left -= _strength;
            break;
        case LEFT:
            // If turning into obsticle, turn right
            if (right > left)
                right -= _strength;
            break;
        case BACK:
            // If droid is heading toward obsticle
            if (left < 0 && right < 0)
            {
                // If droid is turning more to left than right
                // Turn hard left else turn hard right
                if (left < right)
                {
                    left -= _strength;
                    right += _strength;
                }
                else
                {
                    left += _strength;
                    right -= _strength;
                }
            }
            break;
        }
    }
}
