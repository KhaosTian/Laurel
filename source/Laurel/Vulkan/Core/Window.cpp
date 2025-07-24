#include "GLFW/glfw3.h"
#include "Laurel/Core/Log.h"
#include "pch.h"
#include "Laurel/Vulkan/Core/Window.h"

namespace Vulkan {

static void glfwErrorCallback(int error, const char* description) {
    LR_CORE_ERROR("[GLFW {}]: {}", error, description);
}

Window::Window(const WindowConfig& config): config_(config) {
    // glfw 初始化
    int success = glfwInit();
    LR_ASSERT(success == GLFW_TRUE, "GLFW initialization failed");

    // 检查glfw对vulkan的支持
    int support = glfwVulkanSupported();
    LR_ASSERT(support == GLFW_TRUE, "GLFW does not support Vulkan");

    // 初始化window hint
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, config.enable_resize ? GLFW_TRUE : GLFW_FALSE);

    // 获取显示器
    auto monitor_ptr = config.is_fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    // 创建window
    handle_ = glfwCreateWindow(config.width, config.height, config.title.c_str(), monitor_ptr, nullptr);
    LR_ASSERT(handle_ != nullptr, "Failed to create GLFW window");

    // 设置显示位置
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(handle_, (mode->width - config.width) / 2, (mode->height - config.height) / 2);

    // 设置错误回调
    glfwSetErrorCallback(glfwErrorCallback);
}

Window::~Window() {
    if (handle_) {
        glfwDestroyWindow(handle_);
        handle_ = nullptr;
    }
}

VkExtent2D Window::getWindowSize() const {
    int width, height;
    glfwGetWindowSize(handle_, &width, &height);
    return VkExtent2D { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
}

std::vector<const char*> Window::getRequiredInstanceExtensions() const {
    uint32_t                 extension_count     = 0;
    const char**             required_extensions = glfwGetRequiredInstanceExtensions(&extension_count);
    std::vector<const char*> extensions(required_extensions, required_extensions + extension_count);
    return extensions;
}

void Window::pollEvents() const {
    glfwPollEvents();
}
void Window::waitEvents() const {
    glfwWaitEvents();
}
bool Window::shouldClose() const {
    return glfwWindowShouldClose(handle_);
}
} // namespace Vulkan
