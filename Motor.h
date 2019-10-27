#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "Component.h"

class Motor : public Component
{
private:
    int _in1;
    int _in2;
    int _en;
    int _side;

public:
    Motor(int in1, int in2, int en, int side);
    void Update(int *left, int *right, DroidData *data);
};
#endif