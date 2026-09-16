#pragma once

#include <cstdint>

class ADCDriver
{
public:
    explicit ADCDriver(uint8_t pin);

    bool begin();

    int read() const;

private:
    uint8_t _pin;
};