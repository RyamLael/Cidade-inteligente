#pragma once

#include <WString.h>

class WiFiDriver
{
public:
    WiFiDriver(
        const char* ssid,
        const char* password
    );

    bool begin();

    bool isConnected() const;

    String getIPAddress() const;

    const char* getSSID() const;

private:
    const char* _ssid;
    const char* _password;
};