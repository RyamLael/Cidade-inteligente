#pragma once

#include <cstdint>

class LEDDriver
{
public:
    LEDDriver(uint8_t pin);

    bool begin();

    void on();
    void off();

    void setBrightness(uint8_t brightness);

    bool isOn() const;
    uint8_t getBrightness() const;

private:
    uint8_t _pin;

    bool _initialized;
    uint8_t _brightness;
};