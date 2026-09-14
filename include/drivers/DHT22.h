#pragma once

class DHT;

class DHT22Driver {
public:
    DHT22Driver(int pin);

    ~DHT22Driver();

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