/**
 * @file StateLock.h
 * @brief Synchronization macros for thread-safe access to global system state.
 */

#pragma once

#include "SystemState.h"

/**
 * @brief Acquire the global system state mutex with an indefinite wait.
 */
#define STATE_LOCK() \
    xSemaphoreTake(g_stateMutex, portMAX_DELAY)

/**
 * @brief Release the global system state mutex.
 */
#define STATE_UNLOCK() \
    xSemaphoreGive(g_stateMutex)
