#include "Motor.h"
#include <Arduino.h>

Motor::Motor(int in1, int in2, int en, Side side)
{
    _in1 = in1;
    _in2 = in2;
    _en = en;
    _side = side;

    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(en, OUTPUT);
}

void Motor::Update(int left, int right, DroidData *data)
{
    Component::Update(left, right, data);
    switch (_side)
    {
    case LEFT:
    {
        analogWrite(_en, left);
        digitalWrite(_in1, left >= 0);
        digitalWrite(_in2, left < 0);
        break;
    }
    case RIGHT:
    {
        analogWrite(_en, right);
        digitalWrite(_in1, right >= 0);
        digitalWrite(_in2, right < 0);
        break;
    }
    }
}
