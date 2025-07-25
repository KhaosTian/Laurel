#pragma once

#include <vulkan/vulkan.h>
#include <vector>

#include "Laurel/Utils/NonCopyable.h"

namespace Laurel {
class RHIContext final: NonCopyable {
  public:
    RHIContext(const std::vector<const char*>& requiredExtensions);
    ~RHIContext();

    VkInstance       instance() { return m_instance; }
    VkDevice         device() { return m_device; }
    VkPhysicalDevice physical_device() { return m_physical_device; }
    VkQueue          graphics_queue() { return m_graphics_queue; }
    VkQueue          present_queue() { return m_present_queue; }

  private:
    VkInstance       m_instance { nullptr };
    VkDevice         m_device { nullptr };
    VkPhysicalDevice m_physical_device { nullptr };
    VkQueue          m_graphics_queue { nullptr };
    VkQueue          m_present_queue { nullptr };

    VkDebugUtilsMessengerEXT m_debug_messenger { nullptr };

#ifdef LR_DEBUG
    const bool m_enableValidationLayers = true;
#else
    const bool m_enableValidationLayers = false;
#endif

  private:
    void createInstance(const std::vector<const char*>& requiredExtensions);
    void pickPhysicalDevice();
    void createLogicalDevice();

    void setupDebugMessenger();
};
} // namespace Laurel