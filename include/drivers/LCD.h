/**
 * @file LCD.h
 * @brief I2C liquid crystal display (LCD) driver.
 */

#pragma once

#include <cstdint>
#include <WString.h>

class LiquidCrystal_I2C;

/**
 * @brief Driver for controlling I2C alphanumeric LCD displays.
 */
class LCDDriver
{
public:
    /**
     * @brief Construct a new LCDDriver instance.
     *
     * @param address I2C address of the LCD controller.
     * @param cols Number of character columns.
     * @param rows Number of character rows.
     */
    LCDDriver(
        uint8_t address,
        uint8_t cols,
        uint8_t rows
    );

    /**
     * @brief Destroy the LCDDriver instance and free display resources.
     */
    ~LCDDriver();

    /**
     * @brief Initialize the LCD display, backlight, and clear screen.
     *
     * @return true Initialization succeeded.
     * @return false Initialization failed.
     */
    bool begin();

    /**
     * @brief Clear the display and return cursor to home position.
     */
    void clear();

    /**
     * @brief Move cursor to specified column and row position.
     *
     * @param col Zero-based column index.
     * @param row Zero-based row index.
     */
    void setCursor(
        uint8_t col,
        uint8_t row
    );

    /**
     * @brief Print null-terminated C-string at current cursor position.
     *
     * @param text Pointer to null-terminated string to print.
     */
    void print(const char* text);

    /**
     * @brief Print Arduino String object at current cursor position.
     *
     * @param text Reference to Arduino String to print.
     */
    void print(const String& text);

    /**
     * @brief Move cursor to specified position and print C-string.
     *
     * @param col Zero-based column index.
     * @param row Zero-based row index.
     * @param text Pointer to null-terminated string to print.
     */
    void printAt(
        uint8_t col,
        uint8_t row,
        const char* text
    );

    /**
     * @brief Move cursor to specified position and print Arduino String.
     *
     * @param col Zero-based column index.
     * @param row Zero-based row index.
     * @param text Reference to Arduino String to print.
     */
    void printAt(
        uint8_t col,
        uint8_t row,
        const String& text
    );

    /**
     * @brief Overwrite an entire row, padding with spaces to clear remaining columns.
     *
     * @param row Zero-based row index to write.
     * @param text Pointer to text string to display.
     */
    void writeLine(
        uint8_t row,
        const char* text
    );

    /**
     * @brief Overwrite an entire row, padding with spaces to clear remaining columns.
     *
     * @param row Zero-based row index to write.
     * @param text Reference to Arduino String to display.
     */
    void writeLine(
        uint8_t row,
        const String& text
    );

    /**
     * @brief Turn on the LCD backlight.
     */
    void backlight();

    /**
     * @brief Turn off the LCD backlight.
     */
    void noBacklight();

    /**
     * @brief Enable or disable the LCD backlight.
     *
     * @param enable true to turn backlight on, false to turn it off.
     */
    void setBacklight(bool enable);

    /**
     * @brief Check if the LCD has been successfully initialized.
     *
     * @return true Display is initialized.
     * @return false Display is not initialized.
     */
    bool isInitialized() const;

    /**
     * @brief Get the configured I2C address of the LCD.
     *
     * @return uint8_t I2C address.
     */
    uint8_t getAddress() const;

    /**
     * @brief Get the number of columns of the LCD.
     *
     * @return uint8_t Column count.
     */
    uint8_t getCols() const;

    /**
     * @brief Get the number of rows of the LCD.
     *
     * @return uint8_t Row count.
     */
    uint8_t getRows() const;

private:
    /**
     * @brief I2C address of the display.
     */
    uint8_t _address;

    /**
     * @brief Number of text columns.
     */
    uint8_t _cols;

    /**
     * @brief Number of text rows.
     */
    uint8_t _rows;

    /**
     * @brief Initialization status flag.
     */
    bool _initialized;

    /**
     * @brief Pointer to underlying LiquidCrystal_I2C object.
     */
    LiquidCrystal_I2C* _lcd;
};