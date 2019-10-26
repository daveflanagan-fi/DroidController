#include "Tank.h"

void Tank::Setup()
{
    Droid::Setup();

    AddComponent(new Motor(IN1, IN2, EN1, LEFT));
    AddComponent(new Motor(IN3, IN4, EN2, RIGHT));
}
