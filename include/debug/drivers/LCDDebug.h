/**
 * @file LCDDebug.h
 * @brief Diagnostic routines for dual I2C LCD display testing.
 */

#pragma once

/**
 * @brief Initialize I2C bus and both welcome and sensor LCD displays with test banners.
 */
void LCDDebugSetup();

/**
 * @brief Periodically refresh both LCD displays with incrementing counter and simulated telemetry.
 */
void LCDDebugLoop();
