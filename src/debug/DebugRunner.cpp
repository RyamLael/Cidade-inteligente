#include "debug/DebugRunner.h"

#include "debug/DebugConfig.h"

#include "debug/drivers/DHT11Debug.h"
#include "debug/drivers/ServoDebug.h"
#include "debug/drivers/LCDDebug.h"
#include "debug/i2c/I2CScannerDebug.h"

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

        case DEBUG_I2C_SCANNER:
            I2CScannerDebugSetup();
            break;

        case DEBUG_LCD:
            LCDDebugSetup();
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

        case DEBUG_I2C_SCANNER:
            I2CScannerDebugLoop();
            break;

        case DEBUG_LCD:
            LCDDebugLoop();
            break;

        default:
            break;
    }
}