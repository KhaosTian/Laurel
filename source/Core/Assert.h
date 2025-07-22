#pragma once

#include "Core/Base.h"
#include "Core/Log.h"

#ifdef LR_DEBUG
    #define LR_ENABLE_ASSERTS
#endif

#ifdef LR_ENABLE_ASSERTS
    #define LR_ASSERT(x, ...) \
        { \
            if (!(x)) { \
                LR_CLIENT_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); \
                LR_DEBUG_BREAK; \
            } \
        }
    #define LR_CORE_ASSERT(x, ...) \
        { \
            if (!(x)) { \
                LR_CORE_CRITICAL("Assertion Failed: {0}", __VA_ARGS__); \
                LR_DEBUG_BREAK; \
            } \
        }
#else
    #define LR_ASSERT(x, ...)
    #define LR_CORE_ASSERT(x, ...)
#endif