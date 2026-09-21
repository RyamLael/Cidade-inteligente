/**
 * @file ADCDebug.h
 * @brief Diagnostic routines for analog-to-digital converter (ADC) testing.
 */

#pragma once

/**
 * @brief Set up serial communication and initialize ADC driver for debugging.
 */
void ADCDebugSetup();

/**
 * @brief Read analog sensor value repeatedly and output to the serial monitor.
 */
void ADCDebugLoop();