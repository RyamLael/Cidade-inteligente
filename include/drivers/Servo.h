#pragma once

#include <cstdint>

class Servo;

class ServoDriver {

    public:
        ServoDriver(uint8_t pin);

        ~ServoDriver();

        bool begin();

        void open();
        void close();

        void setAngle();
        int getAngle() const;

    private:
        uint8_t _pin;

        uint8_t _angle;
        Servo* _servo;
};