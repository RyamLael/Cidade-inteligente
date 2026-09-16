#pragma once

#include "SystemState.h"

#define STATE_LOCK() \
    xSemaphoreTake(g_stateMutex, portMAX_DELAY)

#define STATE_UNLOCK() \
    xSemaphoreGive(g_stateMutex)