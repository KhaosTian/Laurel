#include "pch.h"
#include "Laurel/Core/Assert.h"
#include "Laurel/Core/Window.h"
#include "Laurel/RHI/RhiContext.h"
#include "Laurel/Rhi/RhiUtils.h"

namespace Laurel {

// DebugMessenger相关函数
namespace {
    VkResult
    CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
        const auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if (func == nullptr) return VK_ERROR_EXTENSION_NOT_PRESENT;
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    }

    void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
        const auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func == nullptr) return;
        func(instance, debugMessenger, pAllocator);
    }

    VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
                                                 VkDebugUtilsMessageTypeFlagsEXT             messageType,
                                                 const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                                                 void*                                       pUserData) {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            LR_CORE_ERROR("Vulkan Debug: {}", pCallbackData->pMessage);
        } else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            LR_CORE_WARN("Vulkan Debug: {}", pCallbackData->pMessage);
        } else {
            LR_CORE_INFO("Vulkan Debug: {}", pCallbackData->pMessage);
        }
        return VK_FALSE;
    }
} // namespace

RhiContext::RhiContext(const Window& window): m_window(window) {
    CreateInstance();
    SetupDebugMessenger();

    CreateSurface();

    PickPhysicalDevice();

    CheckDeviceExtensionSupport();

    CreateLogicalDevice();
}

std::vector<const char*> RhiContext::GetRequiredExtensions() const {
    uint32_t                 extensionCount = 0;
    const char**             glfwExtensions = glfwGetRequiredInstanceExtensions(&extensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + extensionCount);
    if (m_enableValidationLayers) {
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }
    return extensions;
}

bool RhiContext::CheckValidationLayersSupport() const {
    if (!m_enableValidationLayers) return;

    // 获取可用的验证层属性
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> properties(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, properties.data());

    // 检查Vulkan是否支持验证层
    for (auto layerName: m_validationLayers) {
        bool found = false;
        for (const auto& property: properties) {
            if (strcmp(property.layerName, layerName) == 0) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
}

void RhiContext::PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
    createInfo                 = {};
    createInfo.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = DebugCallback;
}

void RhiContext::CreateInstance() {
    if (m_enableValidationLayers && !CheckValidationLayersSupport()) {
        LR_CORE_ERROR("validation layers requested, but not available!");
    }

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
    createInfo.sType            = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // 获取所需的实例扩展
    auto extensions                    = GetRequiredExtensions();
    createInfo.enabledExtensionCount   = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    // 设置验证层
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo {};
    if (m_enableValidationLayers) {
        createInfo.enabledLayerCount   = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();

        PopulateDebugMessengerCreateInfo(debugCreateInfo);
        createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.pNext             = nullptr;
    }

    if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
        LR_CORE_ERROR("failed to create instance");
    }
}

void RhiContext::PickPhysicalDevice() {
    // 获取物理设备列表
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
    if (deviceCount == 0) {
        LR_CORE_ERROR("failed to find GPUs with Vulkan support!");
    }
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
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan surface: {}", VkResultToString(result))
}

bool RhiContext::CheckDeviceExtensionSupport() const {
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

    LR_CORE_ASSERT(requiredExtensions.empty(), "Vulkan device extensions not supported: {}", unsupportedExtensions)
}

bool RhiContext::IsDeviceSuitable(VkPhysicalDevice device) const {
    return FindQueueFamilies(device).IsComplete();
}

QueueFamilyIndices RhiContext::FindQueueFamilies(VkPhysicalDevice device) const {
    QueueFamilyIndices indices;

    // 获取队列族属性
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    LR_CORE_ASSERT(queueFamilyCount > 0, "No Vulkan queue families found");
    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    // 寻找支持图形、呈现和计算的队列族，记录下它们的索引
    for (uint32_t i = 0; i < queueFamilyCount; ++i) {
        const auto& queueFamily = queueFamilies[i];
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) indices.graphics = i;
        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT) indices.compute = i;

        // 检查是否支持呈现
        VkBool32 presentSupport = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);
        if (presentSupport) indices.present = i;

        if (indices.IsComplete()) break;
    }
    return indices;
}

void RhiContext::CreateLogicalDevice() {
    // 队列创建信息
    QueueFamilyIndices indices             = FindQueueFamilies(m_physicalDevice);
    std::set<uint32_t> uniqueQueueFamilies = { indices.graphics.value(), indices.graphics.value(), indices.compute.value() };

    float queuePriorities = { 1.0f };

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos {};
    for (const auto& queueFamily: uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo {};
        queueCreateInfo.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount       = 1;
        queueCreateInfo.pQueuePriorities = &queuePriorities;
        queueCreateInfos.push_back(queueCreateInfo);
    }

    // 设备特性
    VkPhysicalDeviceFeatures physicalDeviceFeatures {};

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
    LR_CORE_ASSERT(result == VK_SUCCESS, "Failed to create Vulkan logical device: {}", VkResultToString(result))
}

void RhiContext::SetupDebugMessenger() {
    if (!m_enableValidationLayers) return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    PopulateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(m_instance, &createInfo, nullptr, &m_debugMessenger) != VK_SUCCESS) {
        LR_CORE_ERROR("failed to set up debug messenger");
    }
}
} // namespace Laurel
