#pragma once

#include <ESPAsyncWebServer.h>

class HttpRoutes
{
public:
    static void configure(
        AsyncWebServer& server,
        AsyncWebSocket& webSocket
    );
};