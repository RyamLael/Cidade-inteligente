/**
 * @file ADC.h
 * @brief Analog-to-digital converter (ADC) input driver.
 */

#pragma once

#include <cstdint>

/**
 * @brief Driver for reading analog sensor values from a specified GPIO pin.
 */
class ADCDriver
{
public:
    /**
     * @brief Construct a new ADCDriver instance.
     *
     * @param pin GPIO pin number configured for analog reading.
     */
    explicit ADCDriver(uint8_t pin);

    /**
     * @brief Initialize the ADC pin as an input.
     *
     * @return true Initialization succeeded.
     * @return false Initialization failed.
     */
    bool begin();

    /**
     * @brief Read the current raw analog value from the configured pin.
     *
     * @return int Raw ADC reading (0 to 4095 on 12-bit ADC).
     */
    int read() const;

private:
    /**
     * @brief GPIO pin assigned to this ADC driver.
     */
    uint8_t _pin;
};