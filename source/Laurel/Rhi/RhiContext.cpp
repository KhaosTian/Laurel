#include "pch.h"
#include "Laurel/Core/Assert.h"
#include "Laurel/Core/Window.h"
#include "Laurel/RHI/RhiContext.h"
#include "Laurel/Rhi/RhiUtils.h"

namespace Laurel {

RhiContext::RhiContext(const Window& window): m_window(window) {
    CheckValidationLayersSupport();

    CreateInstance();
    CreateSurface();

    PickPhysicalDevices();
    FindQueueFamilyIndices();
    CreateLogicalDevice();
}

void RhiContext::CheckValidationLayersSupport() {
    if (!m_enableValidationLayers) return;

    // 获取可用的验证层属性
    uint32_t propertyCount;
    vkEnumerateInstanceLayerProperties(&propertyCount, nullptr);
    std::vector<VkLayerProperties> properties(propertyCount);
    vkEnumerateInstanceLayerProperties(&propertyCount, properties.data());

    // 检查Vulkan是否支持验证层
    for (auto layerName: m_validationLayers) {
        bool found = false;
        for (const auto& property: properties) {
            if (strcmp(property.layerName, layerName) == 0) {
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
    createInfo.enabledLayerCount       = static_cast<uint32_t>(m_validationLayers.size());
    createInfo.ppEnabledLayerNames     = m_validationLayers.data();

    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan instance: {}", VkResultToString(result));
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
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan surface: {}", VkResultToString(result));
}

void RhiContext::CheckDeviceExtensionSupport() {
    // 获取物理设备支持的扩展列表
    uint32_t extensionCount = 0;
    vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, nullptr);
    LR_CORE_ASSERT(extensionCount > 0, "No Vulkan device extensions found");
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(m_physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    // 检查所需的扩展是否都被支持
    std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());
    for (const auto& availableExtension: availableExtensions) {
        requiredExtensions.erase(availableExtension.extensionName);
    }

    if (requiredExtensions.empty()) return;

    // 拼接未被支持的扩展的信息
    std::string unsupportedExtensions;
    for (const auto& extension: requiredExtensions) {
        unsupportedExtensions += std::string(extension) + ", ";
    }

    LR_CORE_ASSERT(requiredExtensions.empty(), "Vulkan device extensions not supported: {}", unsupportedExtensions);
}

void RhiContext::FindQueueFamilyIndices() {
    // 获取队列族属性
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, nullptr);
    LR_CORE_ASSERT(queueFamilyCount > 0, "No Vulkan queue families found");
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &queueFamilyCount, queueFamilies.data());

    // 寻找支持图形、呈现和计算的队列族，记录下它们的索引
    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        const auto& queueFamily = queueFamilies[i];
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) m_queueIndices.graphics = i;
        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) m_queueIndices.compute = i;

        // 检查是否支持呈现
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, i, m_surface, &presentSupport);
        if (presentSupport) m_queueIndices.present = i;

        // 如果所有队列族索引都已找到，则提前返回
        if (m_queueIndices.IsComplete()) return;
    }
}

void RhiContext::CreateLogicalDevice() {
    const std::vector<float> queuePriorities    = { 1.0f };
    const std::set<uint32_t> queueFamilyIndices = { m_queueIndices.graphics.value(), m_queueIndices.present.value(), m_queueIndices.compute.value() };

    // 队列创建信息
    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos {};
    for (const auto& queueFamilyIndex: queueFamilyIndices) {
        VkDeviceQueueCreateInfo queueCreateInfo {};
        queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount       = 1;
        queueCreateInfo.pQueuePriorities = queuePriorities.data();
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // 设备特性
    VkPhysicalDeviceFeatures physicalDeviceFeatures {};
    physicalDeviceFeatures.samplerAnisotropy        = VK_TRUE;
    physicalDeviceFeatures.fragmentStoresAndAtomics = VK_TRUE;

    // 设备创建信息
    VkDeviceCreateInfo deviceCreateInfo {};
    deviceCreateInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos       = queueCreateInfos.data();
    deviceCreateInfo.queueCreateInfoCount    = static_cast<uint32_t>(queueCreateInfos.size());
    deviceCreateInfo.pEnabledFeatures        = &physicalDeviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = m_deviceExtensions.data();
    deviceCreateInfo.enabledExtensionCount   = static_cast<uint32_t>(m_deviceExtensions.size());
    deviceCreateInfo.enabledLayerCount       = 0;

    VkResult result = vkCreateDevice(m_physicalDevice, &deviceCreateInfo, nullptr, &m_device);
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan logical device: {}", VkResultToString(result));
}

void RhiContext::SetupDebugMessenger() {
}
} // namespace Laurel
