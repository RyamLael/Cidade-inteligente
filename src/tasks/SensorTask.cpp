#include "tasks/SensorTask.h"

#include <Arduino.h>

#include "application/SensorService.h"

namespace
{
    SensorService sensorService;
}

void SensorTask::run(
    void* parameter
)
{
    if (!sensorService.begin())
    {
        Serial.println(
            "Falha ao iniciar SensorService"
        );

        vTaskDelete(
            nullptr
        );
    }

    while (true)
    {
        sensorService.update();

        vTaskDelay(
            pdMS_TO_TICKS(1000)
        );
    }
}