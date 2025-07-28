#pragma once

#include <vulkan/vulkan.h>
#include "Laurel/Core/Base.h"
#include "Laurel/Core/Window.h"

namespace Laurel {
class RhiContext {
    LR_NON_COPIABLE(RhiContext)
  public:
    RhiContext(const Window& window);
    ~RhiContext() = default;

    VkInstance       GetInstance() const { return m_instance; }
    VkDevice         GetDevice() const { return m_device; }
    VkPhysicalDevice GetPhysicalDevice() const { return m_physicalDevice; }
    VkQueue          GetGraphicsQueue() const { return m_graphicsQueue; }
    VkQueue          GetPresentQueue() const { return m_presentQueue; }

  private:
    const Window&    m_window;
    VkInstance       m_instance { nullptr };
    VkDevice         m_device { nullptr };
    VkPhysicalDevice m_physicalDevice { nullptr };
    VkQueue          m_graphicsQueue { nullptr };
    VkQueue          m_presentQueue { nullptr };

    VkSurfaceKHR m_surface { nullptr };

    VkDebugUtilsMessengerEXT m_debugMessenger { nullptr };

#ifdef LR_DEBUG
    const bool m_enableValidationLayers = true;
#else
    const bool m_enableValidationLayers = false;
#endif

  private:
    static void CheckVulkanLayersSupport(const std::vector<const char*>& validationLayers);
    void        CreateInstance();
    void        PickPhysicalDevices();
    void        CreateSurface();
    void        CreateLogicalDevice();

    void SetupDebugMessenger();
};
} // namespace Laurel