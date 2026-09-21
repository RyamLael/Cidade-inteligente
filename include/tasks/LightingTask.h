/**
 * @file LightingTask.h
 * @brief FreeRTOS task managing street light dimming and control.
 */

#pragma once

/**
 * @brief Task wrapper executing periodic street lighting updates.
 */
class LightingTask
{
public:
    /**
     * @brief Task entry function executing the lighting control loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};