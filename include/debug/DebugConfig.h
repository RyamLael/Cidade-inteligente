#pragma once

enum DebugModule
{
    DEBUG_NONE,
    DEBUG_DHT11
};

constexpr DebugModule ACTIVE_DEBUG = DEBUG_DHT11;