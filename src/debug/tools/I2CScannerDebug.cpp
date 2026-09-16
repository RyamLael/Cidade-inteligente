#include "debug/tools/I2CScannerDebug.h"

#include <Arduino.h>
#include <Wire.h>

#include "Config.h"

void I2CScannerDebugSetup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("I2CScannerDebugSetup");

    Wire.begin();
}

void I2CScannerDebugLoop()
{
    Serial.println("Scanning I2C bus...");
    Serial.println();

    int nDevices = 0;

    for (uint8_t address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0)
        {
            Serial.println("Found device:");
            Serial.printf("Address (HEX): 0x%02X\n", address);
            Serial.printf("Address (DEC): %d\n", address);
            Serial.println();
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.printf("Unknown error at address 0x%02X\n", address);
        }
    }

    if (nDevices == 0)
    {
        Serial.println("No I2C devices found.");
        Serial.println();
    }

    Serial.println("Scan complete.");
    Serial.println();

    delay(3000);
}
