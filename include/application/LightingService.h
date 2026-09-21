/**
 * @file LightingService.h
 * @brief Service controlling street lighting brightness based on ambient light or manual commands.
 */

#pragma once

/**
 * @brief Application service managing automatic and manual street light dimming.
 */
class LightingService
{
public:
    /**
     * @brief Initialize the street light LED driver and set default brightness.
     *
     * @return true LED driver initialized successfully.
     * @return false LED driver initialization failed.
     */
    bool begin();

    /**
     * @brief Compute target brightness from ambient light or manual setting and update output.
     */
    void update();
};