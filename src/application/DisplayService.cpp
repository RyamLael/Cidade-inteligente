#include "application/DisplayService.h"

#include <cstdio>

#include "Config.h"
#include "SystemState.h"
#include "StateLock.h"

#include "drivers/LCD.h"

namespace
{
    constexpr uint8_t LCD_COLS = 16;
    constexpr uint8_t LCD_ROWS = 2;

    LCDDriver welcomeDisplay(
        LCD_WELCOME_ADDRESS,
        LCD_COLS,
        LCD_ROWS
    );

    LCDDriver sensorDisplay(
        LCD_SENSOR_ADDRESS,
        LCD_COLS,
        LCD_ROWS
    );

    bool initialized = false;
}

bool DisplayService::begin()
{
    bool success = true;

    success &= welcomeDisplay.begin();
    success &= sensorDisplay.begin();

    if (!success)
    {
        return false;
    }

    char cityName[17];

    float temperature;
    float humidity;

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

    g_systemState.cityNameChanged =
        false;

    g_systemState.sensorDisplayChanged =
        false;

    STATE_UNLOCK();

    welcomeDisplay.writeLine(
        0,
        "Bem-vindo a"
    );

    welcomeDisplay.writeLine(
        1,
        cityName
    );

    char temperatureLine[17];
    char humidityLine[17];

    std::snprintf(
        temperatureLine,
        sizeof(temperatureLine),
        "Temp:%4.1f C",
        temperature
    );

    std::snprintf(
        humidityLine,
        sizeof(humidityLine),
        "Umid:%4.1f%%",
        humidity
    );

    sensorDisplay.writeLine(
        0,
        temperatureLine
    );

    sensorDisplay.writeLine(
        1,
        humidityLine
    );

    initialized = true;

    return true;
}

void DisplayService::update()
{
    if (!initialized)
    {
        return;
    }

    bool cityChanged;
    bool sensorChanged;

    char cityName[17];

    float temperature;
    float humidity;

    STATE_LOCK();

    cityChanged =
        g_systemState.cityNameChanged;

    sensorChanged =
        g_systemState.sensorDisplayChanged;

    strncpy(
        cityName,
        g_systemState.cityName,
        sizeof(cityName)
    );

    temperature =
        g_systemState.temperature;

    humidity =
        g_systemState.humidity;

    if (cityChanged)
    {
        g_systemState.cityNameChanged =
            false;
    }

    if (sensorChanged)
    {
        g_systemState.sensorDisplayChanged =
            false;
    }

    STATE_UNLOCK();

    if (cityChanged)
    {
        welcomeDisplay.writeLine(
            1,
            cityName
        );
    }

    if (sensorChanged)
    {
        char temperatureLine[17];
        char humidityLine[17];

        std::snprintf(
            temperatureLine,
            sizeof(temperatureLine),
            "Temp:%4.1f C",
            temperature
        );

        std::snprintf(
            humidityLine,
            sizeof(humidityLine),
            "Umid:%4.1f%%",
            humidity
        );

        sensorDisplay.writeLine(
            0,
            temperatureLine
        );

        sensorDisplay.writeLine(
            1,
            humidityLine
        );
    }
}