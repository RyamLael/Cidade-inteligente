#include "drivers/LCD.h"

#include <LiquidCrystal_I2C.h>
#include <cstdio>

LCDDriver::LCDDriver(uint8_t address, uint8_t cols, uint8_t rows)
    : _address(address), _cols(cols), _rows(rows), _lcd(nullptr)
{
}

LCDDriver::~LCDDriver()
{
    if (_lcd != nullptr)
    {
        delete _lcd;
        _lcd = nullptr;
    }
}

bool LCDDriver::begin()
{
    if (_lcd == nullptr)
    {
        _lcd = new LiquidCrystal_I2C(_address, _cols, _rows);
    }

    _lcd->init();
    _lcd->backlight();
    _lcd->clear();

    return true;
}

void LCDDriver::clear()
{
    if (_lcd != nullptr)
    {
        _lcd->clear();
    }
}

void LCDDriver::setCursor(uint8_t col, uint8_t row)
{
    if (_lcd != nullptr)
    {
        _lcd->setCursor(col, row);
    }
}

void LCDDriver::print(const char* text)
{
    if (_lcd != nullptr && text != nullptr)
    {
        _lcd->print(text);
    }
}

void LCDDriver::print(const String& text)
{
    if (_lcd != nullptr)
    {
        _lcd->print(text);
    }
}

void LCDDriver::printAt(uint8_t col, uint8_t row, const char* text)
{
    if (_lcd != nullptr && text != nullptr)
    {
        _lcd->setCursor(col, row);
        _lcd->print(text);
    }
}

void LCDDriver::printAt(uint8_t col, uint8_t row, const String& text)
{
    if (_lcd != nullptr)
    {
        _lcd->setCursor(col, row);
        _lcd->print(text);
    }
}

void LCDDriver::writeLine(uint8_t row, const char* text)
{
    if (_lcd != nullptr && text != nullptr)
    {
        _lcd->setCursor(0, row);
        char buffer[32];
        std::snprintf(buffer, sizeof(buffer), "%-*.*s", _cols, _cols, text);
        _lcd->print(buffer);
    }
}

void LCDDriver::writeLine(uint8_t row, const String& text)
{
    writeLine(row, text.c_str());
}

void LCDDriver::backlight()
{
    if (_lcd != nullptr)
    {
        _lcd->backlight();
    }
}

void LCDDriver::noBacklight()
{
    if (_lcd != nullptr)
    {
        _lcd->noBacklight();
    }
}

void LCDDriver::setBacklight(bool enable)
{
    if (_lcd != nullptr)
    {
        if (enable)
        {
            _lcd->backlight();
        }
        else
        {
            _lcd->noBacklight();
        }
    }
}

uint8_t LCDDriver::getAddress() const
{
    return _address;
}

uint8_t LCDDriver::getCols() const
{
    return _cols;
}

uint8_t LCDDriver::getRows() const
{
    return _rows;
}
