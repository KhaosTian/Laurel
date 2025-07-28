#include "Laurel/Vulkan/Core/Surface.h"
#include "Laurel/Vulkan/Core/Instance.h"
#include "Laurel/Vulkan/Vulkan.h"
#include "Laurel/Core/Window.h"

namespace Laurel {
Surface::Surface(const Instance& instance): m_instance(instance) {
    Check(glfwCreateWindowSurface(instance.handle(), instance.window().handle(), nullptr, &m_handle), "create window surface");
}

Surface::~Surface() {
    if (m_handle == nullptr) return;

    vkDestroySurfaceKHR(m_instance.handle(), m_handle, nullptr);
    m_handle = nullptr;
}
} // namespace Laurel
