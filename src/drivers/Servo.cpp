#include "drivers/Servo.h"

#include <ESP32Servo.h>
#include <cstdint>

ServoDriver::ServoDriver(uint8_t pin)
    :_pin(pin),
    _angle(0)
    {}
