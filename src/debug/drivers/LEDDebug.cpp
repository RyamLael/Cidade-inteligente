#include "debug/drivers/LEDDebug.h"

#include <Arduino.h>

#include "Config.h"
#include "drivers/LED.h"

static LEDDriver led(
    PIN_LED_POSTE
);

static int brightness = 0;
static int step = 15;

void LEDDebugSetup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE LED");
    Serial.println("====================");

    led.begin();
}

void LEDDebugLoop()
{
    led.setBrightness(brightness);

    Serial.printf(
        "Brightness: %d\n",
        brightness
    );

    brightness += step;

    if (brightness >= 255)
    {
        brightness = 255;
        step = -15;
    }

    if (brightness <= 0)
    {
        brightness = 0;
        step = 15;
    }

    delay(100);
}