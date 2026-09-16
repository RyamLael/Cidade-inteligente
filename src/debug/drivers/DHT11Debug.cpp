#include <Arduino.h>

#include "Config.h"
#include "drivers/DHT11.h"

static DHT11Driver dht(PIN_DHT22);

void DHT11DebugSetup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE DHT22");
    Serial.println("====================");

    dht.begin();
}

void DHT11DebugLoop()
{
    if (dht.read())
    {
        Serial.printf(
            "Temperatura: %.2f C | Umidade: %.2f %%\n",
            dht.getTemperature(),
            dht.getHumidity()
        );
    }
    else
    {
        Serial.println("Falha na leitura do DHT22");
    }

    delay(2000);
}