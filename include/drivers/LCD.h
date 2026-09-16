#pragma once

#include <cstdint>
#include <WString.h>

class LiquidCrystal_I2C;

class LCDDriver
{
public:
    LCDDriver(
        uint8_t address,
        uint8_t cols,
        uint8_t rows
    );

    ~LCDDriver();

    bool begin();

    void clear();

    void setCursor(
        uint8_t col,
        uint8_t row
    );

    void print(const char* text);
    void print(const String& text);

    void printAt(
        uint8_t col,
        uint8_t row,
        const char* text
    );

    void printAt(
        uint8_t col,
        uint8_t row,
        const String& text
    );

    void writeLine(
        uint8_t row,
        const char* text
    );

    void writeLine(
        uint8_t row,
        const String& text
    );

    void backlight();
    void noBacklight();
    void setBacklight(bool enable);

    bool isInitialized() const;

    uint8_t getAddress() const;
    uint8_t getCols() const;
    uint8_t getRows() const;

private:
    uint8_t _address;
    uint8_t _cols;
    uint8_t _rows;

    bool _initialized;

    LiquidCrystal_I2C* _lcd;
};