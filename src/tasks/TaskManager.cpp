#include "tasks/TaskManager.h"

#include <Arduino.h>

#include "tasks/SensorTask.h"
#include "tasks/AnalogTask.h"
#include "tasks/DisplayTask.h"
#include "tasks/GateTask.h"
#include "tasks/LightingTask.h"
#include "tasks/WebServerTask.h"

bool TaskManager::createTasks()
{
    xTaskCreatePinnedToCore(
        SensorTask::run,
        "SensorTask",
        4096,
        nullptr,
        1,
        nullptr,
        1
    );

    xTaskCreatePinnedToCore(
        AnalogTask::run,
        "AnalogTask",
        4096,
        nullptr,
        3,
        nullptr,
        1
    );

    xTaskCreatePinnedToCore(
        GateTask::run,
        "GateTask",
        4096,
        nullptr,
        3,
        nullptr,
        1
    );

    xTaskCreatePinnedToCore(
        LightingTask::run,
        "LightingTask",
        4096,
        nullptr,
        2,
        nullptr,
        1
    );

    xTaskCreatePinnedToCore(
        DisplayTask::run,
        "DisplayTask",
        4096,
        nullptr,
        1,
        nullptr,
        1
    );

    xTaskCreatePinnedToCore(
        WebServerTask::run,
        "WebServerTask",
        8192,
        nullptr,
        1,
        nullptr,
        0
    );

    return true;
}