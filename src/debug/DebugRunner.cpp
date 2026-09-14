#include "debug/DebugRunner.h"
#include "debug/DebugConfig.h"

#include "debug/drivers/DHT11Debug.h"

void DebugSetup()
{
    switch (ACTIVE_DEBUG)
    {
        case DEBUG_DHT11:
            DHT11DebugSetup();
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

        default:
            break;
    }
}