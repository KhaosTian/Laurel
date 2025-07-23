#include "Runtime/Vulkan/Core/Surface.h"
#include "Runtime/Vulkan/Core/Instance.h"
#include "Runtime/Vulkan/Vulkan.h"
#include "Runtime/Vulkan/Core/Window.h"

namespace Vulkan {
Surface::Surface(const Instance& instance): m_instance(instance) {
    VK_CHECK(glfwCreateWindowSurface(instance.handle(), instance.window().handle(), nullptr, &m_handle), "create window surface");
}

Surface::~Surface() {
    if (m_handle == nullptr) return;

    vkDestroySurfaceKHR(m_instance.handle(), m_handle, nullptr);
    m_handle = nullptr;
}
} // namespace Vulkan
