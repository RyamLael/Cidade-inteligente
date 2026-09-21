/**
 * @file Servo.h
 * @brief Servo motor driver for gate barrier actuation.
 */

#pragma once

#include <cstdint>

class Servo;

/**
 * @brief Driver for controlling angular position and movement of a servo motor.
 */
class ServoDriver {

    public:
        /**
         * @brief Construct a new ServoDriver instance.
         *
         * @param pin GPIO pin connected to the servo control signal.
         */
        ServoDriver(uint8_t pin);

        /**
         * @brief Destroy the ServoDriver instance and detach servo.
         */
        ~ServoDriver();

        /**
         * @brief Initialize and attach the servo motor to its control pin.
         *
         * @return true Initialization succeeded.
         * @return false Initialization failed.
         */
        bool begin();

        /**
         * @brief Rotate the servo to the open gate position (5 degrees).
         */
        void open();

        /**
         * @brief Rotate the servo to the closed gate position (90 degrees).
         */
        void close();

        /**
         * @brief Set the servo shaft angle directly.
         *
         * @param angle Target angle in degrees (clamped to 0-180).
         */
        void setAngle(uint8_t angle);

        /**
         * @brief Get the current target angle of the servo.
         *
         * @return int Current angle in degrees.
         */
        int getAngle() const;

    private:
        /**
         * @brief GPIO pin connected to the servo control wire.
         */
        uint8_t _pin;

        /**
         * @brief Current angle in degrees.
         */
        uint8_t _angle;

        /**
         * @brief Pointer to underlying ESP32Servo instance.
         */
        Servo* _servo;
};