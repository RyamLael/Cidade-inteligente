#include "SystemState.h"

SystemState g_systemState;

SemaphoreHandle_t g_stateMutex =
    nullptr;