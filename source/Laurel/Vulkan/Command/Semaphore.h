#pragma once

#include "Laurel/Vulkan/Vulkan.h"

namespace Vulkan {
class Device;
class Semaphore final {
  public:
    explicit Semaphore(const Device& device);
    Semaphore(Semaphore&& other) noexcept;
    ~Semaphore();

    VkSemaphore handle() const { return m_handle; }

  private:
    VkSemaphore   m_handle;
    const Device& m_device;
};
} // namespace Vulkan
