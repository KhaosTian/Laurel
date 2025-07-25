#include "Laurel/Vulkan/Command/Semaphore.h"
#include "Laurel/Vulkan/Core/Device.h"

namespace Laurel {
Semaphore::Semaphore(const Device& device): m_device(device) {
    VkSemaphoreCreateInfo create_info = {};
    create_info.sType                 = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    Check(vkCreateSemaphore(device.handle(), &create_info, nullptr, &m_handle), "create semaphores");
}

Semaphore::Semaphore(Semaphore&& other) noexcept: m_device(other.m_device), m_handle(other.m_handle) {
    other.m_handle = nullptr;
}

Semaphore::~Semaphore() {
    if (m_handle == nullptr) return;
    vkDestroySemaphore(m_device.handle(), m_handle, nullptr);
    m_handle = nullptr;
}
} // namespace Laurel
