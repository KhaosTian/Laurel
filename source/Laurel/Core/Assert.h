#pragma once

#include "Laurel/Core/Base.h"
#include "Laurel/Core/Log.h"

#ifdef LR_DEBUG
    #define LR_ENABLE_ASSERTS
#endif

#ifdef LR_ENABLE_ASSERTS
    #define LR_ASSERT(x, ...) \
        { \
            if (!(x)) { \
                LR_ERROR(__VA_ARGS__); \
                LR_DEBUG_BREAK; \
            } \
        }
    #define LR_CORE_ASSERT(x, ...) \
        { \
            if (!(x)) { \
                LR_CORE_ERROR(__VA_ARGS__); \
                LR_DEBUG_BREAK; \
            } \
        }
#else
    #define LR_ASSERT(x, ...)
    #define LR_CORE_ASSERT(x, ...)
#endif
