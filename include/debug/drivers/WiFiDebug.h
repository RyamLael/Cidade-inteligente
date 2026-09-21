/**
 * @file WiFiDebug.h
 * @brief Diagnostic routines for Wi-Fi SoftAP access point testing.
 */

#pragma once

/**
 * @brief Initialize SoftAP access point and log SSID and IP address to serial output.
 */
void WiFiDebugSetup();

/**
 * @brief Periodically check and print the number of connected client stations to serial monitor.
 */
void WiFiDebugLoop();