#pragma once

#include "Laurel/Vulkan/Vulkan.h"
#include <cstddef>
#include <cstdint>

namespace Laurel {
class DescriptorBinding;
class Device;
class DescriptorPool final {
  public:
    DescriptorPool(DescriptorPool&&) = delete;
    DescriptorPool(const Device& device, const std::vector<DescriptorBinding>& descriptor_bindings, size_t max_sets);
    ~DescriptorPool();

    VkDescriptorPool handle() const { return m_handle; }
    const Device&    device() const { return m_device; }

  private:
    VkDescriptorPool m_handle;
    const Device&    m_device;
};
} // namespace Laurel
