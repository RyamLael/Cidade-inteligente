/**
 * @file DHT11Debug.h
 * @brief Diagnostic routines for DHT11 / DHT22 temperature and humidity sensor testing.
 */

#pragma once

/**
 * @brief Initialize serial communication and begin DHT sensor testing.
 */
void DHT11DebugSetup();

/**
 * @brief Periodically read temperature and humidity and output to serial monitor.
 */
void DHT11DebugLoop();