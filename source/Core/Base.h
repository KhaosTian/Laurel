#pragma once

#ifndef LR_PLATFORM_WINDOWS
    #error UNKNOWN PLATFORM
#endif

#ifdef _MSC_VER
    #define LR_COMPILER_MSVC
#elif
    #error UNSUPPORTED COMPILER
#endif

#ifdef LR_COMPILER_MSVC
    #define LR_FORCE_INLINE __forceinline
    #define LR_DEBUG_BREAK __debugbreak()
#endif

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