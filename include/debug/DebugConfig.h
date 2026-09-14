#pragma once

enum DebugModule
{
    DEBUG_NONE,

    DEBUG_DHT11,

    DEBUG_SERVO
};

constexpr DebugModule ACTIVE_DEBUG = DEBUG_SERVO;