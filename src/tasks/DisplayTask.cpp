#include "tasks/DisplayTask.h"

#include <Arduino.h>

#include "application/DisplayService.h"

namespace
{
    DisplayService displayService;
}

void DisplayTask::run(
    void* parameter
)
{
    displayService.begin();

    while (true)
    {
        displayService.update();

        vTaskDelay(
            pdMS_TO_TICKS(100)
        );
    }
}