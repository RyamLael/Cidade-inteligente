#include "application/GateService.h"

#include "Config.h"

#include "drivers/Servo.h"

namespace
{
    ServoDriver gateServo(
        PIN_SERVO
    );
}

bool GateService::begin()
{
    if (!gateServo.begin())
    {
        return false;
    }

    gateServo.close();

    _isOpen =
        false;

    return true;
}

void GateService::open()
{
    if (_isOpen)
    {
        return;
    }

    gateServo.open();

    _isOpen =
        true;
}

void GateService::close()
{
    if (!_isOpen)
    {
        return;
    }

    gateServo.close();

    _isOpen =
        false;
}

bool GateService::isOpen() const
{
    return _isOpen;
}