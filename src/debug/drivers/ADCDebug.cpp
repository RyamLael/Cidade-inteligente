#include "debug/drivers/ADCDebug.h"

#include <Arduino.h>

#include "Config.h"
#include "drivers/ADC.h"

static ADCDriver ldr(LDR_PIN);

void ADCDebugSetup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE ADC");
    Serial.println("====================");

    ldr.begin();
}

void ADCDebugLoop()
{
    int value = ldr.read();

    Serial.printf(
        "ADC Value: %d\n",
        value
    );

    delay(500);
}