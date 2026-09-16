#include "application/AnalogService.h"

#include "Config.h"
#include "SystemState.h"
#include "StateLock.h"

#include "drivers/ADC.h"

namespace
{
    ADCDriver ambientLdr(
        PIN_LDR_AMBIENT
    );

    ADCDriver gateLdr(
        PIN_LDR_GATE
    );

    ADCDriver gatePot(
        PIN_POT_GATE
    );
}

bool AnalogService::begin()
{
    bool success = true;

    success &= ambientLdr.begin();

    success &= gateLdr.begin();

    success &= gatePot.begin();

    return success;
}

void AnalogService::update()
{
    const uint16_t ambientLight =
        ambientLdr.read();

    const uint16_t gateLight =
        gateLdr.read();

    const uint16_t gateThreshold =
        gatePot.read();

    STATE_LOCK();

    bool changed = false;

    if (
        ambientLight !=
        g_systemState.ambientLight
    )
    {
        g_systemState.ambientLight =
            ambientLight;

        changed = true;
    }

    if (
        gateLight !=
        g_systemState.gateLight
    )
    {
        g_systemState.gateLight =
            gateLight;

        changed = true;
    }

    if (
        gateThreshold !=
        g_systemState.gateThreshold
    )
    {
        g_systemState.gateThreshold =
            gateThreshold;

        changed = true;
    }

    if (changed)
    {
        g_systemState.webStateChanged =
            true;
    }

    STATE_UNLOCK();
}