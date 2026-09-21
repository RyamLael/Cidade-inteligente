/**
 * @file HttpRoutes.h
 * @brief HTTP REST endpoint route registrations for the asynchronous web server.
 */

#pragma once

#include <ESPAsyncWebServer.h>

/**
 * @brief Configures HTTP route endpoints such as status APIs on the web server.
 */
class HttpRoutes
{
public:
    /**
     * @brief Register all HTTP routes and request handlers with the server instance.
     *
     * @param server Reference to the target AsyncWebServer.
     * @param webSocket Reference to the active AsyncWebSocket instance.
     */
    static void configure(
        AsyncWebServer& server,
        AsyncWebSocket& webSocket
    );
};