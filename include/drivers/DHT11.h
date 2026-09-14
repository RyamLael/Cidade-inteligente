#pragma once

class DHT;

class DHT11Driver {
public:
    DHT11Driver(int pin);

    ~DHT11Driver();

    bool begin();
    bool read();

    float getTemperature() const;
    float getHumidity() const;

    bool isValid() const;

private:
    int _pin;

    DHT* _dht;

    float _temperature;
    float _humidity;

    bool _valid;
};