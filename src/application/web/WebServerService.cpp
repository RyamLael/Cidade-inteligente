#include "application/web/WebServerService.h"

#include <LittleFS.h>

#include "Config.h"

#include "drivers/WiFi.h"

#include "application/web/HttpRoutes.h"
#include "application/web/WebSocketHandler.h"

namespace
{
    WiFiDriver wifi(
        WIFI_SSID,
        WIFI_PASSWORD
    );
}

WebServerService::
    WebServerService()
    : _server(80),
      _webSocket("/ws")
{
}

bool WebServerService::begin()
{
    if (!wifi.begin())
    {
        return false;
    }

    Serial.print(
        "SSID: "
    );

    Serial.println(
        wifi.getSSID()
    );

    Serial.print(
        "IP: "
    );

    Serial.println(
        wifi.getIPAddress()
    );

    if (
        !LittleFS.begin(
            true
        )
    )
    {
        return false;
    }

    HttpRoutes::configure(
        _server,
        _webSocket
    );

    WebSocketHandler::
        configure(
            _webSocket
        );

    _server.addHandler(
        &_webSocket
    );

    _server.serveStatic(
        "/",
        LittleFS,
        "/"
    ).setDefaultFile(
        "index.html"
    );

    _server.begin();

    Serial.println(
        "Web server started."
    );

    return true;
}

void WebServerService::process()
{
    _webSocket
        .cleanupClients();
}

void WebServerService::
    publishSystemState()
{
    WebSocketHandler::
        broadcastSystemState(
            _webSocket
        );
}