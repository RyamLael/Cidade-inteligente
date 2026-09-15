#include "drivers/WiFi.h"

#include <WiFi.h>

WiFiDriver::WiFiDriver(
    const char* ssid,
    const char* password
)
    : _ssid(ssid),
      _password(password)
{
}

bool WiFiDriver::begin()
{
    WiFi.softAP(
        _ssid,
        _password
    );

    return true;
}

bool WiFiDriver::isConnected() const
{
    return WiFi.softAPgetStationNum() > 0;
}

String WiFiDriver::getIPAddress() const
{
    return WiFi.softAPIP().toString();
}

const char* WiFiDriver::getSSID() const
{
    return _ssid;
}