/**
 * @file LED.h
 * @brief LED output driver with analog/PWM brightness control.
 */

#pragma once

#include <cstdint>

/**
 * @brief Driver for controlling LED state and dimming levels.
 */
class LEDDriver
{
public:
    /**
     * @brief Construct a new LEDDriver instance.
     *
     * @param pin GPIO pin connected to the LED.
     */
    LEDDriver(uint8_t pin);

    /**
     * @brief Initialize GPIO pin as output and turn LED off.
     *
     * @return true Initialization succeeded.
     * @return false Initialization failed.
     */
    bool begin();

    /**
     * @brief Turn LED fully on at maximum brightness (255).
     */
    void on();

    /**
     * @brief Turn LED completely off (brightness 0).
     */
    void off();

    /**
     * @brief Set LED brightness using PWM duty cycle.
     *
     * @param brightness Brightness level from 0 (off) to 255 (maximum).
     */
    void setBrightness(uint8_t brightness);

    /**
     * @brief Check whether the LED is currently emitting light.
     *
     * @return true LED brightness is greater than zero.
     * @return false LED is completely off.
     */
    bool isOn() const;

    /**
     * @brief Get the current brightness duty cycle of the LED.
     *
     * @return uint8_t Brightness value (0-255).
     */
    uint8_t getBrightness() const;

private:
    /**
     * @brief GPIO pin connected to the LED.
     */
    uint8_t _pin;

    /**
     * @brief Initialization state flag.
     */
    bool _initialized;

    /**
     * @brief Current brightness level (0-255).
     */
    uint8_t _brightness;
};