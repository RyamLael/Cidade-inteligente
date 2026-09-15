#pragma once

enum DebugModule
{
    DEBUG_NONE = 0,

    DEBUG_DHT11 = 1,

    DEBUG_SERVO = 2,

    DEBUG_I2C_SCANNER = 3,

    DEBUG_LCD = 4
};

constexpr DebugModule ACTIVE_DEBUG = DEBUG_LCD;