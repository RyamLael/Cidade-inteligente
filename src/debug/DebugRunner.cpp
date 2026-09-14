#include "debug/DebugRunner.h"
#include "debug/DebugConfig.h"

#include "debug/drivers/DHT22Debug.h"

void DebugSetup()
{
    switch (ACTIVE_DEBUG)
    {
        case DEBUG_DHT22:
            DHT22DebugSetup();
            break;

        default:
            break;
    }
}

void DebugLoop()
{
    switch (ACTIVE_DEBUG)
    {
        case DEBUG_DHT22:
            DHT22DebugLoop();
            break;

        default:
            break;
    }
}