/**
 * @file DisplayService.h
 * @brief Service responsible for managing welcome and sensor LCD outputs.
 */

#pragma once

/**
 * @brief Application service coordinating updates to dual I2C LCD displays.
 */
class DisplayService
{
public:
    /**
     * @brief Initialize both LCD displays and render initial state.
     *
     * @return true Displays were initialized successfully.
     * @return false Display initialization failed.
     */
    bool begin();

    /**
     * @brief Check dirty flags and update LCD screens if city name or sensor readings changed.
     */
    void update();
};