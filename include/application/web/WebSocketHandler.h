#pragma once

#include <ESPAsyncWebServer.h>

class WebSocketHandler
{
public:
    static void configure(
        AsyncWebSocket& webSocket
    );

    static void broadcastSystemState(
        AsyncWebSocket& webSocket
    );

private:
    static void onEvent(
        AsyncWebSocket* server,
        AsyncWebSocketClient* client,
        AwsEventType type,
        void* arg,
        uint8_t* data,
        size_t len
    );
};