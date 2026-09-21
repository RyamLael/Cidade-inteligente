#include "tasks/GateTask.h"

#include <Arduino.h>

#include "SystemState.h"
#include "StateLock.h"

#include "application/GateService.h"

namespace
{
    GateService gateService;

    uint32_t gateOpenTimestamp =
        0;

    constexpr uint32_t GATE_OPEN_TIME_MS =
        2500;
}

void GateTask::run(
    void* parameter
)
{
    if (!gateService.begin())
    {
        Serial.println(
            "Falha ao iniciar GateService"
        );

        vTaskDelete(
            nullptr
        );
    }

    STATE_LOCK();

    g_systemState.gateOpen =
        false;

    g_systemState.gateOpenRequest =
        false;

    g_systemState.gateCloseRequest =
        false;

    STATE_UNLOCK();

    while (true)
    {
        bool gateOpenRequest;
        bool gateCloseRequest;

        uint16_t gateLight;
        uint16_t gateThreshold;

        STATE_LOCK();

        gateOpenRequest =
            g_systemState.gateOpenRequest;

        gateCloseRequest =
            g_systemState.gateCloseRequest;

        gateLight =
            g_systemState.gateLight;

        gateThreshold =
            g_systemState.gateThreshold;

        STATE_UNLOCK();

        /*
         * Fechamento imediato.
         */
        if (gateCloseRequest)
        {
            gateService.close();

            gateOpenTimestamp =
                0;

            STATE_LOCK();

            g_systemState.gateOpen =
                false;

            g_systemState.gateOpenRequest =
                false;

            g_systemState.gateCloseRequest =
                false;

            g_systemState.webStateChanged =
                true;

            STATE_UNLOCK();

            vTaskDelay(
                pdMS_TO_TICKS(50)
            );

            continue;
        }

        /*
         * Solicitação manual.
         */
        if (gateOpenRequest)
        {
            gateOpenTimestamp =
                millis();

            STATE_LOCK();

            g_systemState.gateOpenRequest =
                false;

            STATE_UNLOCK();
        }

        /*
         * Sensor da cancela.
         */
        const bool detection =
            gateLight <
            gateThreshold;

        if (detection)
        {
            gateOpenTimestamp =
                millis();
        }

        bool desiredGateState =
            false;

        if (
            gateOpenTimestamp !=
            0
        )
        {
            desiredGateState =
                (
                    millis() -
                    gateOpenTimestamp
                ) <
                GATE_OPEN_TIME_MS;
        }

        if (
            desiredGateState &&
            !gateService.isOpen()
        )
        {
            gateService.open();

            STATE_LOCK();

            g_systemState.gateOpen =
                true;

            g_systemState.webStateChanged =
                true;

            STATE_UNLOCK();
        }
        else if (
            !desiredGateState &&
            gateService.isOpen()
        )
        {
            gateService.close();

            STATE_LOCK();

            g_systemState.gateOpen =
                false;

            g_systemState.webStateChanged =
                true;

            STATE_UNLOCK();
        }

        vTaskDelay(
            pdMS_TO_TICKS(50)
        );
    }
}