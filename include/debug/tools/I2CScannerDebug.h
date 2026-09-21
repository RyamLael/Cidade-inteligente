/**
 * @file I2CScannerDebug.h
 * @brief Diagnostic utility for scanning and detecting devices on the I2C bus.
 */

#pragma once

/**
 * @brief Initialize serial port and start I2C peripheral for bus scanning.
 */
void I2CScannerDebugSetup();

/**
 * @brief Probe all standard 7-bit I2C addresses (1-126) and report detected devices via serial monitor.
 */
void I2CScannerDebugLoop();
