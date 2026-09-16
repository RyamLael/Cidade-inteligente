#include "tasks/LightingTask.h"

#include <Arduino.h>

#include "application/LightingService.h"

namespace
{
    LightingService lightingService;
}

void LightingTask::run(
    void* parameter
)
{
    lightingService.begin();

    while (true)
    {
        lightingService.update();

        vTaskDelay(
            pdMS_TO_TICKS(100)
        );
    }
}