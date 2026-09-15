#pragma once

enum DebugModule
{
    DEBUG_NONE,

    DEBUG_DHT11,

    DEBUG_SERVO,

    DEBUG_I2C_SCANNER,

    DEBUG_LCD
};

constexpr DebugModule ACTIVE_DEBUG = DEBUG_LCD;