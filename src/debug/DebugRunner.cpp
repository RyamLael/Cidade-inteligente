#include "debug/DebugRunner.h"

#include <Arduino.h>

#include "debug/drivers/ADCDebug.h"
#include "debug/drivers/DHT11Debug.h"
#include "debug/drivers/LCDDebug.h"
#include "debug/drivers/ServoDebug.h"
#include "debug/tools/I2CScannerDebug.h"
#include "debug/drivers/WiFiDebug.h"
#include "debug/drivers/LEDDebug.h"

static int selectedDebug = 0;

static void ShowMenu()
{
    Serial.println();
    Serial.println("====================");
    Serial.println("DEBUG MENU");
    Serial.println("====================");
    Serial.println("1 - DHT11");
    Serial.println("2 - Servo");
    Serial.println("3 - LCD");
    Serial.println("4 - I2C Scanner");
    Serial.println("5 - ADC");
    Serial.println("6 - WiFi");
    Serial.println("7 - LED");
    Serial.println();
    Serial.print("Choose option: ");
}

void DebugSetup()
{
    Serial.begin(115200);

    delay(1000);

    while (selectedDebug == 0)
    {
        ShowMenu();

        while (!Serial.available())
        {
            delay(10);
        }

        selectedDebug = Serial.parseInt();

        switch (selectedDebug)
        {
            case 1:
                DHT11DebugSetup();
                break;

            case 2:
                ServoDebugSetup();
                break;

            case 3:
                LCDDebugSetup();
                break;

            case 4:
                I2CScannerDebugSetup();
                break;

            case 5:
                ADCDebugSetup();
                break;
            case 6:
                WiFiDebugSetup();
                break;
            case 7:
                LEDDebugSetup();
                break;

            default:
                Serial.println();
                Serial.println("Invalid option.");
                selectedDebug = 0;
                break;
        }
    }
}

void DebugLoop()
{
    switch (selectedDebug)
    {
        case 1:
            DHT11DebugLoop();
            break;

        case 2:
            ServoDebugLoop();
            break;

        case 3:
            LCDDebugLoop();
            break;

        case 4:
            I2CScannerDebugLoop();
            break;

        case 5:
            ADCDebugLoop();
            break;
        case 6:
            WiFiDebugLoop();
            break;
        case 7:
            LEDDebugLoop();
            break;

        default:
            break;
    }
}