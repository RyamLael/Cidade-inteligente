/**
 * @file AnalogTask.h
 * @brief FreeRTOS task responsible for polling analog sensors.
 */

#pragma once

/**
 * @brief Task wrapper executing periodic ADC sensor readings.
 */
class AnalogTask
{
public:
    /**
     * @brief Task entry function executing the analog polling loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};