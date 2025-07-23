#include "Laurel/Vulkan/Core/Surface.h"
#include "Laurel/Vulkan/Core/Instance.h"
#include "Laurel/Vulkan/Vulkan.h"
#include "Laurel/Vulkan/Core/Window.h"

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
