#pragma once

#include <cstdint>
#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>

struct SystemState
{
    float temperature = 0.0f;
    float humidity = 0.0f;

    uint16_t ambientLight = 0;
    uint16_t gateLight = 0;

    uint16_t gateThreshold = 0;

    bool gateOpen = false;

    bool manualGateControl = false;

    uint8_t streetLightBrightness = 0;

    bool manualLightingControl = false;

    char cityName[17] = "Sobral";

    bool cityNameChanged = true;

    bool sensorDisplayChanged = true;

    bool webStateChanged = true;

    bool brightnessChanged = true;
};

extern SystemState g_systemState;

extern SemaphoreHandle_t g_stateMutex;