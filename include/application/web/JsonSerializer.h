/**
 * @file JsonSerializer.h
 * @brief JSON serialization utility for exporting system state to web clients.
 */

#pragma once

#include <Arduino.h>

/**
 * @brief Utility class for serializing current system telemetry and states into JSON strings.
 */
class JsonSerializer
{
public:
    /**
     * @brief Snapshot the global system state in a thread-safe manner and serialize to JSON.
     *
     * @return String Formatted JSON payload containing all system state fields.
     */
    static String serializeSystemState();
};