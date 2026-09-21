/**
 * @file AnalogService.h
 * @brief Service responsible for sampling analog sensors and updating system state.
 */

#pragma once

/**
 * @brief Application service managing analog inputs (ambient LDR, gate LDR, potentiometer threshold).
 */
class AnalogService
{
public:
    /**
     * @brief Initialize all configured ADC driver channels.
     *
     * @return true All ADC drivers initialized successfully.
     * @return false One or more ADC driver initializations failed.
     */
    bool begin();

    /**
     * @brief Sample analog inputs and commit updated readings to global system state.
     */
    void update();
};