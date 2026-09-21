/**
 * @file DisplayTask.h
 * @brief FreeRTOS task managing LCD screen updates.
 */

#pragma once

/**
 * @brief Task wrapper executing periodic LCD display refreshes.
 */
class DisplayTask
{
public:
    /**
     * @brief Task entry function executing the display update loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};