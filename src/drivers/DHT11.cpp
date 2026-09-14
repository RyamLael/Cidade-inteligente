#include "drivers/DHT11.h"

#include <DHT.h>

#define DHT_TYPE DHT11

DHT11Driver::DHT11Driver(int pin)
    : _pin(pin),
      _dht(nullptr),
      _temperature(0.0f),
      _humidity(0.0f),
      _valid(false)
{
}

bool DHT11Driver::begin()
{
    _dht = new DHT(_pin, DHT_TYPE);

    _dht->begin();

    return true;
}

bool DHT11Driver::read()
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

float DHT11Driver::getTemperature() const
{
    return _temperature;
}

float DHT11Driver::getHumidity() const
{
    return _humidity;
}

bool DHT11Driver::isValid() const
{
    return _valid;
}

DHT11Driver::~DHT11Driver()
{
    if (_dht != nullptr)
    {
        delete _dht;
        _dht = nullptr;
    }
}