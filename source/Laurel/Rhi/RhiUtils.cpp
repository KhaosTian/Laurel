#include "pch.h"
#include "Laurel/Rhi/RhiUtils.h"

namespace Laurel {
void VerifyVulkanResult(const char* message, VkResult result, const char* resultString, const char* file, int line) {
    if (result == VK_SUCCESS) return;
#ifdef LR_ENABLE_ASSERTS
    LR_CORE_ASSERT(false, "message: {} in {}:{}", resultString, file, line);
#else
    LR_CORE_FATAL("message: {} in {}:{}", resultString, file, line);
#endif
}
} // namespace Laurel