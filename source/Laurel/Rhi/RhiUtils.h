#pragma once

#include "vulkan/vulkan_core.h"

#include <vulkan/vulkan.h>

namespace Laurel {
const char* VkResultToString(VkResult result);
}


#if defined(LR_DEBUG)
    #define VK_CHECK(x) \
        do \
        { \
            VkResult result = (x); \
            if (result != VK_SUCCESS) \
            { \
                LR_CORE_ASSERT(false, "Vulkan call failed with error: {} ({})", \
                    Laurel::VkResultToString(result), static_cast<int>(result)); \
            } \
        } while (false)

#else
    #define VK_CHECK(x) \
        do \
        { \
            VkResult result = (x); \
            if (result != VK_SUCCESS) \
            { \
                LR_CORE_FATAL("Vulkan call failed with error: {} ({})", \
                    Laurel::VkResultToString(result), static_cast<int>(result)); \
            } \
        } while (false)

#endif