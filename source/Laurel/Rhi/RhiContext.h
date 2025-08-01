#pragma once

#include <vulkan/vulkan.h>
#include "Laurel/Core/Base.h"
#include "Laurel/Core/Window.h"
#include "Laurel/Rhi/RhiStruct.h"

namespace Laurel {
class RhiContext {
    LR_NON_COPIABLE(RhiContext)
  public:
    explicit RhiContext(const Window& window);
    ~RhiContext() = default;

    VkInstance       GetInstance() const { return m_instance; }
    VkDevice         GetDevice() const { return m_device; }
    VkPhysicalDevice GetPhysicalDevice() const { return m_physicalDevice; }
    VkQueue          GetGraphicsQueue() const { return m_graphicsQueue; }
    VkQueue          GetPresentQueue() const { return m_presentQueue; }
    VkQueue          GetComputeQueue() const { return m_computeQueue; }

  private:
    const Window&      m_window;
    VkInstance         m_instance { nullptr };
    VkDevice           m_device { nullptr };
    VkPhysicalDevice   m_physicalDevice { nullptr };
    VkQueue            m_graphicsQueue { nullptr };
    VkQueue            m_presentQueue { nullptr };
    VkQueue            m_computeQueue { nullptr };
    VkSurfaceKHR       m_surface { nullptr };

    VkDebugUtilsMessengerEXT m_debugMessenger { nullptr };

    const std::vector<const char*> m_validationLayers = { "VK_LAYER_KHRONOS_validation" };
    const std::vector<const char*> m_deviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

#ifdef LR_DEBUG
    const bool m_enableValidationLayers = true;
#else
    const bool m_enableValidationLayers = false;
#endif

  private:
    std::vector<const char*> GetRequiredExtensions() const;

    void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);

    bool CheckValidationLayersSupport() const;
    bool CheckDeviceExtensionSupport() const;

    void CreateInstance();
    void CreateSurface();
    void CreateLogicalDevice();

    bool IsDeviceSuitable(VkPhysicalDevice device) const;
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device) const;
    void PickPhysicalDevice();


    void SetupDebugMessenger();
};
} // namespace Laurel