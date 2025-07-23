#pragma once

#include "Runtime/Vulkan/Vulkan.h"
#include <cstdint>
#include <string>
#include <vector>

namespace Vulkan {
class Device;

class ShaderModule final {
  public:
    ShaderModule(ShaderModule&&) = delete;
    ShaderModule(const Device& device, const std::string& filename);
    ShaderModule(const Device& device, const std::vector<uint8_t>& code);
    ~ShaderModule();

    VkShaderModule                  handle() const { return m_handle; }
    VkPipelineShaderStageCreateInfo CreateShaderStage(VkShaderStageFlagBits stage) const;

  private:
    VkShaderModule m_handle;
    const Device&  m_device;

    static std::vector<uint8_t> ReadFile(const std::string& filename);
};
} // namespace Vulkan