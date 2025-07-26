#include "pch.h"
#include "Laurel/Core/Window.h"

namespace Laurel {
namespace {
    void glfwErrorCallback(const int error, const char* const description) {
        LR_CORE_ERROR("GLFW: {} (code: {})\n", description, error);
    }

    void glfwKeyCallback(GLFWwindow* window, const int key, const int scancode, const int action, const int mods) {
        if (auto* const this_ = static_cast<Window*>(glfwGetWindowUserPointer(window)); this_->on_key) {
            this_->on_key(key, scancode, action, mods);
        }
    }

    void glfwCursorPositionCallback(GLFWwindow* window, const double pos_x, const double pos_y) {
        if (auto* const this_ = static_cast<Window*>(glfwGetWindowUserPointer(window)); this_->on_cursor_position) {
            this_->on_cursor_position(pos_x, pos_y);
        }
    }

    void glfwMouseButtonCallback(GLFWwindow* window, const int button, const int action, const int mods) {
        if (auto* const this_ = static_cast<Window*>(glfwGetWindowUserPointer(window)); this_->on_mouse_button) {
            this_->on_mouse_button(button, action, mods);
        }
    }

    void glfwScrollCallback(GLFWwindow* window, const double offset_x, const double offset_y) {
        if (auto* const this_ = static_cast<Window*>(glfwGetWindowUserPointer(window)); this_->on_scroll) {
            this_->on_scroll(offset_x, offset_y);
        }
    }
} // namespace

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
    m_window = glfwCreateWindow(desc.width, desc.height, desc.title.c_str(), monitor_ptr, nullptr);
    LR_CORE_ASSERT(m_window != nullptr, "Failed to create GLFW window");

    // 设置显示位置
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_window, (mode->width - desc.width) / 2, (mode->height - desc.height) / 2);

    // 设置glfw事件回调
    glfwSetErrorCallback(glfwErrorCallback);
    glfwSetKeyCallback(m_window, glfwKeyCallback);
    glfwSetCursorPosCallback(m_window, glfwCursorPositionCallback);
    glfwSetScrollCallback(m_window, glfwScrollCallback);
    glfwSetMouseButtonCallback(m_window, glfwMouseButtonCallback);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

Vector2i Window::getWindowSize() const {
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return Vector2i { width, height };
}

std::vector<const char*> Window::getRequiredInstanceExtensions() {
    uint32_t extension_count = 0;
    if (const char** required_extensions = glfwGetRequiredInstanceExtensions(&extension_count)) {
        return { required_extensions, required_extensions + extension_count };
    }
    return {};
}

void Window::pollEvents() const {
    glfwPollEvents();
}

void Window::waitEvents() const {
    glfwWaitEvents();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}
} // namespace Laurel
