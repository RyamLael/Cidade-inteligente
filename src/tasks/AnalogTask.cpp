#include "tasks/AnalogTask.h"

#include <Arduino.h>

#include "application/AnalogService.h"

namespace
{
    AnalogService analogService;
}

void AnalogTask::run(
    void* parameter
)
{
    if (!analogService.begin())
    {
        Serial.println(
            "AnalogService falhou"
        );

        vTaskDelete(
            nullptr
        );
    }

    while (true)
    {
        analogService.update();

        vTaskDelay(
            pdMS_TO_TICKS(50)
        );
    }
}