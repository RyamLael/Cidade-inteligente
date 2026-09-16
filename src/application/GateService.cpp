#include "application/GateService.h"

#include "Config.h"
#include "SystemState.h"
#include "StateLock.h"

#include "drivers/Servo.h"

namespace
{
    ServoDriver gateServo(
        PIN_SERVO
    );

    bool currentGateState =
        false;
}

bool GateService::begin()
{
    if (!gateServo.begin())
    {
        return false;
    }

    gateServo.close();

    currentGateState =
        false;

    STATE_LOCK();

    g_systemState.gateOpen =
        false;

    STATE_UNLOCK();

    return true;
}

void GateService::update()
{
    bool manualGateControl;
    bool gateOpen;

    uint16_t gateLight;
    uint16_t gateThreshold;

    STATE_LOCK();

    manualGateControl =
        g_systemState.manualGateControl;

    gateOpen =
        g_systemState.gateOpen;

    gateLight =
        g_systemState.gateLight;

    gateThreshold =
        g_systemState.gateThreshold;

    STATE_UNLOCK();

    bool desiredGateState;

    if (manualGateControl)
    {
        desiredGateState =
            gateOpen;
    }
    else
    {
        desiredGateState =
            gateLight <
            gateThreshold;
    }

    if (
        desiredGateState ==
        currentGateState
    )
    {
        return;
    }

    if (desiredGateState)
    {
        gateServo.open();
    }
    else
    {
        gateServo.close();
    }

    currentGateState =
        desiredGateState;

    STATE_LOCK();

    g_systemState.gateOpen =
        currentGateState;

    g_systemState.webStateChanged =
        true;

    STATE_UNLOCK();
}