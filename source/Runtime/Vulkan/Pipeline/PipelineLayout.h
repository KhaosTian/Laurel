#pragma once

#include "Runtime/Vulkan/Vulkan.h"

namespace Vulkan {
class Device;
class DescriptorSetLayout;

class PipelineLayout final {
  public:
    PipelineLayout(PipelineLayout&&) = delete;
    PipelineLayout(const Device& device, const DescriptorSetLayout& descriptor_layout, const VkPushConstantRange* push_constant_ranges);
    ~PipelineLayout();

    VkPipelineLayout handle() const { return m_handle; }
    const Device&    device() const { return m_device; }

  private:
    VkPipelineLayout m_handle;
    const Device&    m_device;
};
} // namespace Vulkan