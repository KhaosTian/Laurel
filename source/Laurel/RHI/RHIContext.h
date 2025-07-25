#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "Laurel/Utils/NonCopyable.h"

namespace Laurel {
class RHIContext final: NonCopyable {
  public:
    RHIContext(const std::vector<const char*>& requiredExtensions);
    ~RHIContext();

  private:
    VkInstance m_instance { nullptr };
    VkDevice   m_device { nullptr };
    VkQueue    m_graphics_queue { nullptr };
    VkQueue    m_present_queue { nullptr };
};
} // namespace Laurel