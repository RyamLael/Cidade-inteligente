#include "drivers/LED.h"

#include <Arduino.h>

LEDDriver::LEDDriver(uint8_t pin)
    : _pin(pin),
      _initialized(false),
      _brightness(0)
{
}

bool LEDDriver::begin()
{
    pinMode(_pin, OUTPUT);

    off();

    _initialized = true;

    return true;
}

void LEDDriver::on()
{
    setBrightness(255);
}

void LEDDriver::off()
{
    setBrightness(0);
}

void LEDDriver::setBrightness(uint8_t brightness)
{
    if (!_initialized)
    {
        return;
    }

    _brightness = brightness;

    analogWrite(
        _pin,
        brightness
    );
}

bool LEDDriver::isOn() const
{
    return _brightness > 0;
}

uint8_t LEDDriver::getBrightness() const
{
    return _brightness;
}