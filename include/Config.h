/**
 * @file Config.h
 * @brief Hardware pinout, network configuration, and system constants.
 */

#pragma once

#include <cstdint>

// ===== DHT =====

/**
 * @brief GPIO pin connected to the DHT11 temperature and humidity sensor data line.
 */
constexpr uint8_t PIN_DHT11 = 4;

/**
 * @brief Alias GPIO pin for DHT22 sensor compatibility.
 */
constexpr uint8_t PIN_DHT22 = PIN_DHT11;

// ===== Servo =====

/**
 * @brief GPIO pin assigned to the gate servo motor PWM signal.
 */
constexpr uint8_t PIN_SERVO = 18;

// ===== LEDs =====

/**
 * @brief GPIO pin for the street light LED (poste).
 */
constexpr uint8_t PIN_LED_POSTE = 19;

// ===== Laser =====

/**
 * @brief GPIO pin used to drive the gate laser emitter.
 */
constexpr uint8_t PIN_LASER = 23;

// ===== I2C =====

/**
 * @brief I2C Serial Data (SDA) pin.
 */
constexpr uint8_t PIN_I2C_SDA = 21;

/**
 * @brief I2C Serial Clock (SCL) pin.
 */
constexpr uint8_t PIN_I2C_SCL = 22;

// ===== LCD Addresses =====

/**
 * @brief I2C bus address for the welcome LCD display.
 */
constexpr uint8_t LCD_WELCOME_ADDRESS = 0x3F;

/**
 * @brief I2C bus address for the environmental sensor LCD display.
 */
constexpr uint8_t LCD_SENSOR_ADDRESS  = 0x3E;

// ===== ADC =====

/**
 * @brief ADC input pin connected to the ambient light LDR sensor.
 */
constexpr uint8_t PIN_LDR_AMBIENT = 34;

/**
 * @brief ADC input pin connected to the gate barrier LDR sensor.
 */
constexpr uint8_t PIN_LDR_GATE    = 35;

/**
 * @brief ADC input pin connected to the gate threshold potentiometer.
 */
constexpr uint8_t PIN_POT_GATE    = 32;

/**
 * @brief ADC resolution in bits.
 */
#define ADC_RESOLUTION 12

// ===== WIFI ===== 

/**
 * @brief Default SSID for the ESP32 SoftAP access point.
 */
constexpr const char* WIFI_SSID = "CidadeInteligente";

/**
 * @brief Default password for the ESP32 SoftAP access point.
 */
constexpr const char* WIFI_PASSWORD = "1cidade23456";