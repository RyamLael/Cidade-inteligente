#include "application/SensorService.h"

#include <cmath>

#include "Config.h"
#include "SystemState.h"
#include "StateLock.h"

#include "drivers/DHT11.h"

namespace
{
    DHT11Driver dht(
        PIN_DHT11
    );
}

bool SensorService::begin()
{
    return dht.begin();
}

bool SensorService::update()
{
    const float temperature =
        dht.getTemperature();

    const float humidity =
        dht.getHumidity();

    if (
        std::isnan(temperature) ||
        std::isnan(humidity)
    )
    {
        return false;
    }

    STATE_LOCK();

    bool changed = false;

    if (
        temperature !=
        g_systemState.temperature
    )
    {
        g_systemState.temperature =
            temperature;

        changed = true;
    }

    if (
        humidity !=
        g_systemState.humidity
    )
    {
        g_systemState.humidity =
            humidity;

        changed = true;
    }

    if (changed)
    {
        g_systemState.sensorDisplayChanged =
            true;

        g_systemState.webStateChanged =
            true;
    }

    STATE_UNLOCK();

    return true;
}