#include "pch.h"
#include "Laurel/Core/Window.h"

namespace Laurel {

static void glfwErrorCallback(int error, const char* description) {
    LR_CORE_ERROR("[GLFW {}]: {}", error, description);
}

Window::Window(const WindowDesc& desc): m_desc(desc) {
    // glfw 初始化
    int success = glfwInit();
    LR_CORE_ASSERT(success == GLFW_TRUE, "GLFW initialization failed");

    // 检查glfw对vulkan的支持
    int support = glfwVulkanSupported();
    LR_CORE_ASSERT(support == GLFW_TRUE, "GLFW does not support Vulkan");

    // 初始化window hint
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, desc.enable_resize ? GLFW_TRUE : GLFW_FALSE);

    // 获取显示器
    auto monitor_ptr = desc.is_fullscreen ? glfwGetPrimaryMonitor() : nullptr;

    // 创建window
    m_handle = glfwCreateWindow(desc.width, desc.height, desc.title.c_str(), monitor_ptr, nullptr);
    LR_CORE_ASSERT(m_handle != nullptr, "Failed to create GLFW window");

    // 设置显示位置
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_handle, (mode->width - desc.width) / 2, (mode->height - desc.height) / 2);

    // 设置错误回调
    glfwSetErrorCallback(glfwErrorCallback);
}

Window::~Window() {
    if (m_handle) {
        glfwDestroyWindow(m_handle);
        m_handle = nullptr;
    }
}

Vector2f Window::getWindowSize() const {
    int width, height;
    glfwGetWindowSize(m_handle, &width, &height);
    return Vector2f { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };
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
    return glfwWindowShouldClose(m_handle);
}
} // namespace Laurel
