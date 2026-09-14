#include "drivers/DHT22.h"

#include <DHT.h>

#define DHT_TYPE DHT22

DHT22Driver::DHT22Driver(int pin)
    : _pin(pin),
      _dht(nullptr),
      _temperature(0.0f),
      _humidity(0.0f),
      _valid(false)
{
}

bool DHT22Driver::begin()
{
    _dht = new DHT(_pin, DHT_TYPE);

    _dht->begin();

    return true;
}

bool DHT22Driver::read()
{
    if (_dht == nullptr)
    {
        _valid = false;
        return false;
    }

    float temperature = _dht->readTemperature();
    float humidity = _dht->readHumidity();

    if (isnan(temperature) || isnan(humidity))
    {
        _valid = false;
        return false;
    }

    _temperature = temperature;
    _humidity = humidity;
    _valid = true;

    return true;
}

float DHT22Driver::getTemperature() const
{
    return _temperature;
}

float DHT22Driver::getHumidity() const
{
    return _humidity;
}

bool DHT22Driver::isValid() const
{
    return _valid;
}

DHT22Driver::~DHT22Driver()
{
    if (_dht != nullptr)
    {
        delete _dht;
        _dht = nullptr;
    }
}