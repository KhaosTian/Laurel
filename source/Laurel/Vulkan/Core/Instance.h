#pragma once

#include "Laurel/Vulkan/Vulkan.h"

namespace Laurel {
class Window;

class Instance final {
  public:
    Instance(Instance&&) = delete;
    Instance(const Window& window, const std::vector<const char*>& validationLayers);
    ~Instance();

    VkInstance                           handle() const { return m_handle; }
    const std::vector<const char*>&      instance_extensions() const { return m_instance_extensions; }
    const std::vector<VkPhysicalDevice>& vk_physical_devices() const { return m_physical_devices; }
    const Window&                        window() const { return m_window; }

  private:
    VkInstance    m_handle {};
    const Window& m_window;

    std::vector<VkPhysicalDevice> m_physical_devices;
    std::vector<const char*>      m_instance_extensions;
    uint32_t                      m_api_version { VK_API_VERSION_1_0 };

    void CheckValidationLayersSupport(const std::vector<const char*>& validation_layers) const;
};
} // namespace Laurel
