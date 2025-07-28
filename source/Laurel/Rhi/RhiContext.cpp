#include "Laurel/Core/Window.h"
#include "pch.h"
#include "Laurel/RHI/RhiContext.h"

namespace Laurel {

static const std::vector<const char*> s_ValidationLayers = { "VK_LAYER_KHRONOS_validation" };

RhiContext::RhiContext(const Window& window): m_window(window) {
    CheckVulkanLayersSupport(s_ValidationLayers);
    CreateInstance();
}

void RhiContext::CheckVulkanLayersSupport(const std::vector<const char*>& layerNames) {
    // 获取可用的验证层属性
    uint32_t propertyCount;
    vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);
    std::vector<VkLayerProperties> properties(propertyCount);
    vkEnumerateInstanceLayerProperties(&propertyCount, properties.data());

    // 检查Vulkan是否支持验证层
    for (auto layerName: layerNames) {
        bool found = false;
        for (const auto& layerProperties: properties) {
            if (strcmp(layerProperties.layerName, layerName) == 0) {
                found = true;
                break;
            }
        }
        LR_CORE_ASSERT(found == true, "Validation layers not supported");
    }
}

void RhiContext::CreateInstance() {
    // 获取所需的实例扩展
    auto extensions = m_window.GetRequiredInstanceExtensions();
    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    // 创建应用信息
    VkApplicationInfo appInfo {};
    appInfo.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName   = "Laurel";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName        = "Laurel";
    appInfo.engineVersion      = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion         = VK_API_VERSION_1_0;

    // 创建实例创建信息
    VkInstanceCreateInfo createInfo {};
    createInfo.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo        = &appInfo;
    createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();
    createInfo.enabledLayerCount       = static_cast<uint32_t>(s_ValidationLayers.size());
    createInfo.ppEnabledLayerNames     = s_ValidationLayers.data();

    int result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance: {}", result)
}

void RhiContext::PickPhysicalDevices() {
    // 获取物理设备列表
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    LR_CORE_ASSERT(deviceCount > 0, "No Vulkan physical devices found");
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, physicalDevices.data());

    // 有独显和集显的情况下，优先选择独立显卡
    for (const auto& device: physicalDevices) {
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(device, &deviceProperties);
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
            m_physicalDevice = device;
            return;
        }
    }

    // 如果没有独立显卡，则选择第一个物理设备
    m_physicalDevice = physicalDevices[0];
}

void RhiContext::CreateSurface() {
    // 创建Vulkan表面
    VkResult result = glfwCreateWindowSurface(m_instance, m_window.GetHandle(), nullptr, &m_surface);
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan surface: {}", result);
}

void RhiContext::CreateLogicalDevice() {
}

void RhiContext::SetupDebugMessenger() {
}
} // namespace Laurel
