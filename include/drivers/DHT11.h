/**
 * @file DHT11.h
 * @brief Driver for the DHT11 temperature and humidity sensor.
 */

#pragma once

class DHT;

/**
 * @brief Driver responsible for interfacing with DHT11 digital humidity and temperature sensors.
 */
class DHT11Driver {
public:
    /**
     * @brief Construct a new DHT11Driver instance.
     *
     * @param pin GPIO pin connected to the sensor data line.
     */
    DHT11Driver(int pin);

    /**
     * @brief Destroy the DHT11Driver instance and release underlying resources.
     */
    ~DHT11Driver();

    /**
     * @brief Initialize the DHT sensor communication.
     *
     * @return true Initialization succeeded.
     * @return false Initialization failed.
     */
    bool begin();

    /**
     * @brief Sample temperature and humidity from the sensor.
     *
     * @return true Reading was successful and data is valid.
     * @return false Reading failed or sensor returned NaN.
     */
    bool read();

    /**
     * @brief Get the most recently read temperature value.
     *
     * @return float Temperature in degrees Celsius.
     */
    float getTemperature() const;

    /**
     * @brief Get the most recently read humidity percentage.
     *
     * @return float Relative humidity percentage (0-100%).
     */
    float getHumidity() const;

    /**
     * @brief Check whether the last sensor read was valid.
     *
     * @return true Last reading was valid.
     * @return false Last reading was invalid or failed.
     */
    bool isValid() const;

private:
    /**
     * @brief GPIO pin used for sensor communication.
     */
    int _pin;

    /**
     * @brief Pointer to underlying Adafruit DHT sensor instance.
     */
    DHT* _dht;

    /**
     * @brief Cached temperature reading in Celsius.
     */
    float _temperature;

    /**
     * @brief Cached humidity reading in percentage.
     */
    float _humidity;

    /**
     * @brief Flag indicating validity of cached readings.
     */
    bool _valid;
};