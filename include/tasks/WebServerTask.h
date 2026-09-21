/**
 * @file WebServerTask.h
 * @brief FreeRTOS task managing web server housekeeping and WebSocket event dispatch.
 */

#pragma once

/**
 * @brief Task wrapper running the web server event loop and WebSocket state publishing.
 */
class WebServerTask
{
public:
    /**
     * @brief Task entry function executing the web server background loop.
     *
     * @param parameter FreeRTOS task parameter pointer (unused).
     */
    static void run(
        void* parameter
    );
};