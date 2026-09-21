/**
 * @file WiFi.h
 * @brief Wi-Fi driver managing the ESP32 SoftAP access point mode.
 */

#pragma once

#include <WString.h>

/**
 * @brief Driver responsible for establishing and monitoring the SoftAP wireless network.
 */
class WiFiDriver
{
public:
    /**
     * @brief Construct a new WiFiDriver instance.
     *
     * @param ssid Network name (SSID) for the SoftAP.
     * @param password Network security passphrase for the SoftAP.
     */
    WiFiDriver(
        const char* ssid,
        const char* password
    );

    /**
     * @brief Start the Wi-Fi interface in SoftAP access point mode.
     *
     * @return true SoftAP started successfully.
     * @return false SoftAP startup failed.
     */
    bool begin();

    /**
     * @brief Check whether any client stations are currently connected to the SoftAP.
     *
     * @return true At least one client is connected.
     * @return false No clients are connected.
     */
    bool isConnected() const;

    /**
     * @brief Get the assigned IP address of the SoftAP as a string.
     *
     * @return String SoftAP IP address.
     */
    String getIPAddress() const;

    /**
     * @brief Get the configured network SSID.
     *
     * @return const char* Pointer to the SSID string.
     */
    const char* getSSID() const;

private:
    /**
     * @brief Access point network SSID.
     */
    const char* _ssid;

    /**
     * @brief Access point network password.
     */
    const char* _password;
};