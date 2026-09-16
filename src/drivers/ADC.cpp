#include "drivers/ADC.h"

#include <Arduino.h>

ADCDriver::ADCDriver(uint8_t pin)
    : _pin(pin)
{
}

bool ADCDriver::begin()
{
    pinMode(_pin, INPUT);

    return true;
}

int ADCDriver::read() const
{
    return analogRead(_pin);
}