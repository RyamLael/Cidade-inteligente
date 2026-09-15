#pragma once

#include <cstdint>

// ===== DHT =====
constexpr uint8_t PIN_DHT11 = 4;
constexpr uint8_t PIN_DHT22 = PIN_DHT11; // Alias for backward compatibility

// ===== LDR =====
constexpr uint8_t PIN_LDR_LIGHT = 34;
constexpr uint8_t PIN_LDR_GATE  = 35;

// ===== Servo =====
constexpr uint8_t PIN_SERVO = 18;

// ===== LEDs =====
constexpr uint8_t PIN_LED_POSTE = 19;

// ===== Laser =====
constexpr uint8_t PIN_LASER = 23;

// ===== I2C =====
constexpr uint8_t PIN_I2C_SDA = 21;
constexpr uint8_t PIN_I2C_SCL = 22;

// ===== LCD Addresses =====
constexpr uint8_t LCD_WELCOME_ADDRESS = 0x3F;
constexpr uint8_t LCD_SENSOR_ADDRESS  = 0x3E;