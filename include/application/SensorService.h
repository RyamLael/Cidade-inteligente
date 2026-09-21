/**
 * @file SensorService.h
 * @brief Service responsible for acquiring environmental data from the DHT11 sensor.
 */

#pragma once

/**
 * @brief Application service managing periodic DHT11 temperature and humidity sampling.
 */
class SensorService
{
public:
    /**
     * @brief Initialize the DHT11 sensor driver.
     *
     * @return true Sensor driver initialized successfully.
     * @return false Sensor driver initialization failed.
     */
    bool begin();

    /**
     * @brief Read latest temperature and humidity values and commit them to system state.
     *
     * @return true Sensor read and state update succeeded.
     * @return false Sensor read failed.
     */
    bool update();
};