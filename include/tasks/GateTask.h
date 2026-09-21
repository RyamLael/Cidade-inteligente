/**
 * @file GateTask.h
 * @brief FreeRTOS task managing gate automation logic and servo actuation.
 */

#pragma once

/**
 * @brief Task wrapper executing the access gate control and obstacle detection loop.
 */
class GateTask
{
public:
    /**
     * @brief Task entry function executing the gate automation and manual control loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};