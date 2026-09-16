#include "tasks/WebServerTask.h"

#include <Arduino.h>

#include "SystemState.h"
#include "StateLock.h"

#include "application/web/WebServerService.h"

namespace
{
    WebServerService webServer;
}

void WebServerTask::run(
    void* parameter
)
{
    if (!webServer.begin())
    {
        Serial.println(
            "Falha ao iniciar WebServer"
        );

        vTaskDelete(
            nullptr
        );
    }

    while (true)
    {
        webServer.process();

        bool publish = false;

        STATE_LOCK();

        publish =
            g_systemState.webStateChanged;

        if (publish)
        {
            g_systemState.webStateChanged =
                false;
        }

        STATE_UNLOCK();

        if (publish)
        {
            webServer
                .publishSystemState();
        }

        vTaskDelay(
            pdMS_TO_TICKS(100)
        );
    }
}