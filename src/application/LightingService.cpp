#include "application/LightingService.h"

#include <Arduino.h>

#include "Config.h"
#include "SystemState.h"
#include "StateLock.h"

#include "drivers/LED.h"

namespace
{
    LEDDriver streetLight(
        PIN_LED_POSTE
    );

    uint8_t currentBrightness =
        255;
}

bool LightingService::begin()
{
    if (!streetLight.begin())
    {
        return false;
    }

    streetLight.setBrightness(
        currentBrightness
    );

    return true;
}

void LightingService::update()
{
    bool manualLightingControl;

    uint16_t ambientLight;

    uint8_t requestedBrightness;

    STATE_LOCK();

    manualLightingControl =
        g_systemState.manualLightingControl;

    ambientLight =
        g_systemState.ambientLight;

    requestedBrightness =
        g_systemState.streetLightBrightness;

    STATE_UNLOCK();

    uint8_t desiredBrightness;

    if (manualLightingControl)
    {
        desiredBrightness =
            requestedBrightness;
    }
    else
    {
        desiredBrightness =
            map(
                ambientLight,
                0,
                4095,
                255,
                0
            );
    }

    if (
        desiredBrightness ==
        currentBrightness
    )
    {
        return;
    }

    currentBrightness =
        desiredBrightness;

    streetLight.setBrightness(
        currentBrightness
    );

    STATE_LOCK();

    g_systemState.streetLightBrightness =
        currentBrightness;

    g_systemState.brightnessChanged =
        true;

    g_systemState.webStateChanged =
        true;

    STATE_UNLOCK();
}