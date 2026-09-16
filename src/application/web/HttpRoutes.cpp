#include "application/web/HttpRoutes.h"

#include "application/web/JsonSerializer.h"

void HttpRoutes::configure(
    AsyncWebServer& server,
    AsyncWebSocket& webSocket
)
{
    server.on(
        "/api/status",
        HTTP_GET,
        [](
            AsyncWebServerRequest*
                request
        )
        {
            request->send(
                200,
                "application/json",
                JsonSerializer::
                    serializeSystemState()
            );
        }
    );
}