/**
 * @file LEDDebug.h
 * @brief Diagnostic routines for street light LED PWM brightness testing.
 */

#pragma once

/**
 * @brief Initialize LED driver and serial port for brightness debug tests.
 */
void LEDDebugSetup();

/**
 * @brief Cycle LED brightness up and down in steps using PWM duty cycle.
 */
void LEDDebugLoop();