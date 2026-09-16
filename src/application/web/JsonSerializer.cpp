#include "application/web/JsonSerializer.h"

#include <ArduinoJson.h>

#include "SystemState.h"
#include "StateLock.h"

String JsonSerializer::serializeSystemState()
{
    JsonDocument json;

    char cityName[17];

    float temperature;
    float humidity;

    uint16_t ambientLight;
    uint16_t gateLight;
    uint16_t gateThreshold;

    bool gateOpen;
    bool manualGateControl;

    uint8_t streetLightBrightness;
    bool manualLightingControl;

    STATE_LOCK();

    strncpy(
        cityName,
        g_systemState.cityName,
        sizeof(cityName)
    );

    temperature =
        g_systemState.temperature;

    humidity =
        g_systemState.humidity;

    ambientLight =
        g_systemState.ambientLight;

    gateLight =
        g_systemState.gateLight;

    gateThreshold =
        g_systemState.gateThreshold;

    gateOpen =
        g_systemState.gateOpen;

    manualGateControl =
        g_systemState.manualGateControl;

    streetLightBrightness =
        g_systemState.streetLightBrightness;

    manualLightingControl =
        g_systemState.manualLightingControl;

    STATE_UNLOCK();

    json["city"] =
        cityName;

    json["temperature"] =
        temperature;

    json["humidity"] =
        humidity;

    json["ambientLight"] =
        ambientLight;

    json["gateLight"] =
        gateLight;

    json["gateThreshold"] =
        gateThreshold;

    json["gateOpen"] =
        gateOpen;

    json["manualGateControl"] =
        manualGateControl;

    json["streetLightBrightness"] =
        streetLightBrightness;

    json["manualLightingControl"] =
        manualLightingControl;

    String output;

    serializeJson(
        json,
        output
    );

    return output;
}