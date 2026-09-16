#include "application/web/WebSocketHandler.h"

#include <ArduinoJson.h>
#include <cstring>

#include "SystemState.h"
#include "StateLock.h"

#include "application/web/JsonSerializer.h"

namespace
{
    AsyncWebSocket* g_webSocket =
        nullptr;
}

void WebSocketHandler::configure(
    AsyncWebSocket& webSocket
)
{
    g_webSocket =
        &webSocket;

    webSocket.onEvent(
        WebSocketHandler::onEvent
    );
}

void WebSocketHandler::broadcastSystemState(
    AsyncWebSocket& webSocket
)
{
    webSocket.textAll(
        JsonSerializer::
            serializeSystemState()
    );
}

void WebSocketHandler::onEvent(
    AsyncWebSocket* server,
    AsyncWebSocketClient* client,
    AwsEventType type,
    void* arg,
    uint8_t* data,
    size_t len
)
{
    switch (type)
    {
        case WS_EVT_CONNECT:
        {
            Serial.print(
                "WS CONNECT - Client "
            );

            Serial.println(
                client->id()
            );

            client->text(
                JsonSerializer::
                    serializeSystemState()
            );

            break;
        }

        case WS_EVT_DISCONNECT:
        {
            Serial.print(
                "WS DISCONNECT - Client "
            );

            Serial.println(
                client->id()
            );

            break;
        }

        case WS_EVT_DATA:
        {
            String message;

            for (
                size_t i = 0;
                i < len;
                ++i
            )
            {
                message +=
                    static_cast<char>(
                        data[i]
                    );
            }

            JsonDocument json;

            DeserializationError error =
                deserializeJson(
                    json,
                    message
                );

            if (error)
            {
                Serial.print(
                    "JSON ERROR: "
                );

                Serial.println(
                    error.c_str()
                );

                return;
            }

            const char* command =
                json["command"];

            if (command == nullptr)
            {
                Serial.println(
                    "COMMAND AUSENTE"
                );

                return;
            }

            if (
                strcmp(
                    command,
                    "set_city"
                ) == 0
            )
            {
                const char* city =
                    json["city"];

                if (city == nullptr)
                {
                    return;
                }

                STATE_LOCK();

                strncpy(
                    g_systemState.cityName,
                    city,
                    sizeof(
                        g_systemState.cityName
                    ) - 1
                );

                g_systemState.cityName[
                    sizeof(
                        g_systemState.cityName
                    ) - 1
                ] = '\0';

                g_systemState.cityNameChanged =
                    true;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "open_gate"
                ) == 0
            )
            {
                STATE_LOCK();

                g_systemState.gateOpenRequest =
                    true;

                g_systemState.gateCloseRequest =
                    false;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "close_gate"
                ) == 0
            )
            {
                STATE_LOCK();

                g_systemState.gateCloseRequest =
                    true;

                g_systemState.gateOpenRequest =
                    false;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "auto_gate"
                ) == 0
            )
            {
                STATE_LOCK();

                g_systemState.gateOpenRequest =
                    false;

                g_systemState.gateCloseRequest =
                    false;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "set_brightness"
                ) == 0
            )
            {
                STATE_LOCK();

                g_systemState.manualLightingControl =
                    true;

                g_systemState.streetLightBrightness =
                    json["brightness"] | 0;

                g_systemState.brightnessChanged =
                    true;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "auto_lighting"
                ) == 0
            )
            {
                STATE_LOCK();

                g_systemState.manualLightingControl =
                    false;

                g_systemState.webStateChanged =
                    true;

                STATE_UNLOCK();
            }
            else if (
                strcmp(
                    command,
                    "request_state"
                ) == 0
            )
            {
                client->text(
                    JsonSerializer::
                        serializeSystemState()
                );
            }
            else
            {
                Serial.print(
                    "COMANDO DESCONHECIDO: "
                );

                Serial.println(
                    command
                );
            }

            break;
        }

        case WS_EVT_PONG:
        {
            break;
        }

        case WS_EVT_ERROR:
        {
            Serial.println(
                "WS ERROR"
            );

            break;
        }

        default:
        {
            break;
        }
    }
}