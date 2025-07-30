#pragma once

#include "vulkan/vulkan_core.h"

#include <vulkan/vulkan.h>

namespace Laurel {
void        VerifyVulkanResult(const char* message, VkResult result, const char* vkFunction, const char* file, int line);
} // namespace Laurel

#define VK_CHECK(x, msg) Laurel::VerifyVulkanResult(msg, x, #x, __FILE__, __LINE__);