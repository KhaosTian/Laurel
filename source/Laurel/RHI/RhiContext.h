#pragma once

#include <vulkan/vulkan.h>
#include <vector>

namespace Laurel {
class RhiContext {
    LR_NON_COPIABLE(RhiContext)
  public:
    explicit RhiContext(const std::vector<const char*>& required_extensions);
    ~RhiContext() = default;

    VkInstance       instance() const { return m_instance; }
    VkDevice         device() const { return m_device; }
    VkPhysicalDevice physicalDevice() const { return m_physical_device; }
    VkQueue          graphicsQueue() const { return m_graphics_queue; }
    VkQueue          presentQueue() const { return m_present_queue; }

  private:
    VkInstance       m_instance { nullptr };
    VkDevice         m_device { nullptr };
    VkPhysicalDevice m_physical_device { nullptr };
    VkQueue          m_graphics_queue { nullptr };
    VkQueue          m_present_queue { nullptr };

    VkDebugUtilsMessengerEXT m_debug_messenger { nullptr };

#ifdef LR_DEBUG
    const bool m_enable_validation_layers = true;
#else
    const bool m_enableValidationLayers = false;
#endif

  private:
    void createInstance();
    void pickPhysicalDevice();
    void createLogicalDevice();

    void setupDebugMessenger();
};
} // namespace Laurel