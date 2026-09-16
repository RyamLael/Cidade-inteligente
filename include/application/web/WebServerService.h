#pragma once

#include <ESPAsyncWebServer.h>

class WebServerService
{
public:
    WebServerService();

    bool begin();

    void process();

    void publishSystemState();

private:
    AsyncWebServer _server;
    AsyncWebSocket _webSocket;
};