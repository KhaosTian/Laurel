#pragma once

#include "Laurel/Vulkan/Vulkan.h"

namespace Laurel {
class Instance;

class DebugUtilsMessenger final {
  public:
    DebugUtilsMessenger(DebugUtilsMessenger&&) = delete;
    explicit DebugUtilsMessenger(const Instance& instance);
    ~DebugUtilsMessenger();

    VkDebugUtilsMessengerEXT handle() const { return m_handle; }
    const Instance&          instance() const { return m_instance; }

    // 调试回调函数
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      message_severity,
                                                        VkDebugUtilsMessageTypeFlagsEXT             message_type,
                                                        const VkDebugUtilsMessengerCallbackDataEXT* callback_data,
                                                        void*                                       user_data);

  private:
    VkDebugUtilsMessengerEXT m_handle { VK_NULL_HANDLE };
    const Instance&          m_instance;

    inline VkResult
    CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger);
    inline void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT callback, const VkAllocationCallbacks* pAllocator);
};

} // namespace Laurel