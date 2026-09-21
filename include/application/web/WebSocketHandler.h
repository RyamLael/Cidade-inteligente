/**
 * @file WebSocketHandler.h
 * @brief WebSocket event dispatcher and client message parser.
 */

#pragma once

#include <ESPAsyncWebServer.h>

/**
 * @brief Handler responsible for processing incoming WebSocket events, commands, and broadcasts.
 */
class WebSocketHandler
{
public:
    /**
     * @brief Attach event callback listener to the provided WebSocket instance.
     *
     * @param webSocket Reference to the AsyncWebSocket to configure.
     */
    static void configure(
        AsyncWebSocket& webSocket
    );

    /**
     * @brief Broadcast current system state JSON message to all connected clients.
     *
     * @param webSocket Reference to the AsyncWebSocket channel.
     */
    static void broadcastSystemState(
        AsyncWebSocket& webSocket
    );

private:
    /**
     * @brief Internal callback for WebSocket client events (connect, disconnect, data reception, errors).
     *
     * @param server Pointer to the WebSocket server instance.
     * @param client Pointer to the client socket triggering the event.
     * @param type Event type identifier (e.g., WS_EVT_CONNECT, WS_EVT_DATA).
     * @param arg Event argument pointer.
     * @param data Pointer to incoming binary/text data buffer.
     * @param len Number of bytes in the data buffer.
     */
    static void onEvent(
        AsyncWebSocket* server,
        AsyncWebSocketClient* client,
        AwsEventType type,
        void* arg,
        uint8_t* data,
        size_t len
    );
};