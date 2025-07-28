#pragma once

#ifdef LR_PLATFORM_WINDOWS
    #define NOMINMAX
#elif
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

#define LR_NON_COPIABLE(ClassName) \
  private: \
    ClassName(const ClassName&)            = delete; \
    ClassName& operator=(const ClassName&) = delete; \
    ClassName(ClassName&&)                 = delete; \
    ClassName& operator=(ClassName&&)      = delete;
