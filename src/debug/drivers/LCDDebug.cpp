#include "debug/drivers/LCDDebug.h"

#include <Arduino.h>
#include <Wire.h>

#include "Config.h"
#include "drivers/LCD.h"

static LCDDriver welcomeDisplay(LCD_WELCOME_ADDRESS, 16, 2);
static LCDDriver sensorDisplay(LCD_SENSOR_ADDRESS, 16, 2);

static uint32_t counter = 0;

void LCDDebugSetup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("====================");
    Serial.println("TESTE DUAL LCD");
    Serial.println("====================");

    Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL);

    Serial.printf("Iniciando Welcome Display em 0x%02X...\n", LCD_WELCOME_ADDRESS);
    welcomeDisplay.begin();
    welcomeDisplay.writeLine(0, "Cidade Intel.");
    welcomeDisplay.writeLine(1, "Bem-vindo!");

    Serial.printf("Iniciando Sensor Display em 0x%02X...\n", LCD_SENSOR_ADDRESS);
    sensorDisplay.begin();
    sensorDisplay.writeLine(0, "Temp: 26.5 C");
    sensorDisplay.writeLine(1, "Umid: 55.0 %");

    Serial.println("Displays inicializados com sucesso!");
}

void LCDDebugLoop()
{
    counter++;

    char buffer[17];
    snprintf(buffer, sizeof(buffer), "Contador: %lu", (unsigned long)counter);
    welcomeDisplay.writeLine(1, buffer);

    float fakeTemp = 24.0f + (counter % 10) * 0.5f;
    float fakeHum = 50.0f + (counter % 20);
    char sensorBuf[17];
    snprintf(sensorBuf, sizeof(sensorBuf), "T:%.1fC U:%.0f%%", fakeTemp, fakeHum);
    sensorDisplay.writeLine(1, sensorBuf);

    Serial.printf("[DEBUG LCD] %s | %s\n", buffer, sensorBuf);

    delay(2000);
}
