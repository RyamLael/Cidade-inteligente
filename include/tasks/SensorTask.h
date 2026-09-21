/**
 * @file SensorTask.h
 * @brief FreeRTOS task responsible for periodic DHT11 environmental readings.
 */

#pragma once

/**
 * @brief Task wrapper executing the environmental sensor acquisition loop.
 */
class SensorTask
{
public:
    /**
     * @brief Task entry function executing the DHT11 periodic sampling loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};