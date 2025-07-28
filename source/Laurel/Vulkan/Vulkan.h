#pragma once

#include "Laurel/Core/Log.h"
#include <vulkan/vulkan.h>

namespace Laurel {
void        Check(VkResult result, const char* operation);
const char* ToString(const VkResult result);
} // namespace Laurel
