#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "pinout.h"

struct JoystickReading {
    // TODO: Define your struct here.

};

void setupJoystick();
JoystickReading readJoystick();

#endif