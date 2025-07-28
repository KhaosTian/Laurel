#pragma once

#include "Laurel/Vulkan/Resource/DescriptorBinding.h"
#include "Laurel/Vulkan/Vulkan.h"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <vector>

namespace Laurel {
class Device;
class DescriptorSets;
class DescriptorSetLayout;
class DescriptorPool;

class DescriptorSetManager final {
  public:
    DescriptorSetManager(DescriptorSetManager&&) = delete;
    DescriptorSetManager(const Device& device, const std::vector<DescriptorBinding>& bindings, size_t max_sets);
    ~DescriptorSetManager();

    const DescriptorSetLayout& descriptor_set_layout() const { return *m_set_layout; }
    DescriptorSets&            descriptor_sets() const { return *m_sets; }

  private:
    std::unique_ptr<DescriptorPool>      m_pool;
    std::unique_ptr<DescriptorSetLayout> m_set_layout;
    std::unique_ptr<DescriptorSets>      m_sets;
};
} // namespace Laurel
