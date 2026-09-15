#include "debug/drivers/WiFiDebug.h"

#include <Arduino.h>

#include "Config.h"
#include "drivers/WiFi.h"

static WiFiDriver wifi(
    WIFI_SSID,
    WIFI_PASSWORD
);

void WiFiDebugSetup()
{
    Serial.begin(115200);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE WIFI");
    Serial.println("====================");

    wifi.begin();

    Serial.printf(
        "SSID: %s\n",
        wifi.getSSID()
    );

    Serial.printf(
        "IP: %s\n",
        wifi.getIPAddress().c_str()
    );
}

void WiFiDebugLoop()
{
    Serial.printf(
        "Connected devices: %d\n",
        wifi.isConnected()
    );

    delay(2000);
}