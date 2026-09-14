#include "debug/DebugRunner.h"

#include "debug/DebugConfig.h"

#include "debug/drivers/DHT11Debug.h"
#include "debug/drivers/ServoDebug.h"

void DebugSetup()
{
    switch (ACTIVE_DEBUG)
    {
        case DEBUG_DHT11:
            DHT11DebugSetup();
            break;

        case DEBUG_SERVO:
            ServoDebugSetup();
            break;

        default:
            break;
    }
}

void DebugLoop()
{
    switch (ACTIVE_DEBUG)
    {
        case DEBUG_DHT11:
            DHT11DebugLoop();
            break;

        case DEBUG_SERVO:
            ServoDebugLoop();
            break;

        default:
            break;
    }
}