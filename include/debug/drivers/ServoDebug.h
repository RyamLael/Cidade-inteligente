/**
 * @file ServoDebug.h
 * @brief Diagnostic routines for gate servo motor angle and motion testing.
 */

#pragma once

/**
 * @brief Initialize serial monitor and attach gate servo driver.
 */
void ServoDebugSetup();

/**
 * @brief Sweep servo through predefined angles (5, 45, 90, 135, 180 degrees) and test open/close routines.
 */
void ServoDebugLoop();