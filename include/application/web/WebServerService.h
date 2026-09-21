/**
 * @file WebServerService.h
 * @brief Service hosting the asynchronous HTTP server and WebSocket communication interface.
 */

#pragma once

#include <ESPAsyncWebServer.h>

/**
 * @brief Application service managing web server lifecycle, static filesystem hosting, and WebSocket dispatch.
 */
class WebServerService
{
public:
    /**
     * @brief Construct a new WebServerService initializing HTTP server on port 80 and WebSocket endpoint at /ws.
     */
    WebServerService();

    /**
     * @brief Start Wi-Fi SoftAP, mount LittleFS filesystem, configure routes, and start web server.
     *
     * @return true Web server and dependencies started successfully.
     * @return false Failed to start Wi-Fi or mount LittleFS filesystem.
     */
    bool begin();

    /**
     * @brief Periodically perform housekeeping tasks such as cleaning disconnected WebSocket clients.
     */
    void process();

    /**
     * @brief Broadcast the latest serialized system state to all connected WebSocket clients.
     */
    void publishSystemState();

private:
    /**
     * @brief Asynchronous HTTP web server instance.
     */
    AsyncWebServer _server;

    /**
     * @brief Asynchronous WebSocket endpoint instance for real-time bi-directional messaging.
     */
    AsyncWebSocket _webSocket;
};