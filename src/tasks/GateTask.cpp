#include "tasks/GateTask.h"

#include <Arduino.h>

#include "application/GateService.h"

namespace
{
    GateService gateService;
}

void GateTask::run(
    void* parameter
)
{
    gateService.begin();

    while (true)
    {
        gateService.update();

        vTaskDelay(
            pdMS_TO_TICKS(50)
        );
    }
}