/**
 * @file SystemState.h
 * @brief Global system state structure and synchronization primitives.
 */

#pragma once

#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

/**
 * @brief Shared state representation containing all sensor readings, actuator states, and control flags.
 */
struct SystemState
{
    /**
     * @brief Current ambient temperature in degrees Celsius.
     */
    float temperature = 0.0f;

    /**
     * @brief Current relative humidity percentage.
     */
    float humidity = 0.0f;

    /**
     * @brief Ambient light ADC level from the outdoor LDR sensor.
     */
    uint16_t ambientLight = 0;

    /**
     * @brief Gate light ADC level from the laser barrier LDR sensor.
     */
    uint16_t gateLight = 0;

    /**
     * @brief Gate trigger threshold ADC reading set via potentiometer.
     */
    uint16_t gateThreshold = 0;

    /**
     * @brief Current physical state of the gate (true if open, false if closed).
     */
    bool gateOpen = false;

    /**
     * @brief Flag indicating manual gate override via web interface.
     */
    bool manualGateControl = false;

    /**
     * @brief Request flag to open the gate manually.
     */
    bool gateOpenRequest = false;

    /**
     * @brief Request flag to close the gate manually.
     */
    bool gateCloseRequest = false;

    /**
     * @brief Current street light PWM duty cycle (0 to 255).
     */
    uint8_t streetLightBrightness = 0;

    /**
     * @brief Flag indicating manual lighting override via web interface.
     */
    bool manualLightingControl = false;

    /**
     * @brief Name of the city displayed on the welcome LCD.
     */
    char cityName[17] = "Sobral";

    /**
     * @brief Dirty flag indicating the city name was updated and needs refresh.
     */
    bool cityNameChanged = true;

    /**
     * @brief Dirty flag indicating temperature or humidity readings changed for LCD update.
     */
    bool sensorDisplayChanged = true;

    /**
     * @brief Dirty flag indicating system state changed and needs WebSocket broadcast.
     */
    bool webStateChanged = true;

    /**
     * @brief Dirty flag indicating street light brightness changed.
     */
    bool brightnessChanged = true;
};

/**
 * @brief Global singleton instance of the system state.
 */
extern SystemState g_systemState;

/**
 * @brief FreeRTOS mutex handle protecting access to g_systemState.
 */
extern SemaphoreHandle_t g_stateMutex;