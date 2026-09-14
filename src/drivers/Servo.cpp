#include "drivers/Servo.h"

#include <ESP32Servo.h>
#include <cstdint>

ServoDriver::ServoDriver(uint8_t pin)
    :_pin(pin),
    _angle(0),
    _servo(nullptr)
    {
    }

ServoDriver::~ServoDriver()
{
    delete _servo;
    _servo = nullptr;
}

bool ServoDriver::begin()
{
    if (_servo != nullptr)
    {
        return true;
    }

    _servo = new Servo();
    _servo->attach(_pin);

    return true;
}

void ServoDriver::setAngle(uint8_t angle)
{
    if (_servo == nullptr)
    {
        return;
    }

    if (angle > 180)
    {
        angle = 180;
    }

    _angle = angle;

    _servo->write(angle);
}

void ServoDriver::open(){
    setAngle(5);
}

void ServoDriver::close(){
    setAngle(90);
}

int ServoDriver::getAngle() const
{
    return _angle;
}