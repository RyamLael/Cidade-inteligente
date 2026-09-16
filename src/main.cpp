#include <Arduino.h>

#include "SystemState.h"
#include "tasks/TaskManager.h"

void setup()
{
    Serial.begin(115200);

    g_stateMutex =
        xSemaphoreCreateMutex();

    if (g_stateMutex == nullptr)
    {
        while (true)
        {
            delay(1000);
        }
    }

    TaskManager::createTasks();
}

void loop()
{
    vTaskDelete(nullptr);
}