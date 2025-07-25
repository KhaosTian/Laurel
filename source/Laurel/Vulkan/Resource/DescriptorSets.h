#pragma once

#include "Laurel/Vulkan/Vulkan.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Laurel {
class Device;
class DescriptorSetLayout;
class DescriptorPool;
class Buffer;
class ImageView;

class DescriptorSets final {
  public:
    DescriptorSets(DescriptorSets&&) = delete;
    DescriptorSets(const DescriptorPool& descriptor_pool, const DescriptorSetLayout& descriptor_layout, std::map<uint32_t, VkDescriptorType> binding_types, size_t size);
    ~DescriptorSets();

    VkDescriptorSet handle(uint32_t index) const { return m_descriptor_sets[index]; }

    VkWriteDescriptorSet Bind(uint32_t index, uint32_t binding, const VkDescriptorBufferInfo& buffer_info, uint32_t count = 1) const;
    VkWriteDescriptorSet Bind(uint32_t index, uint32_t binding, const VkDescriptorImageInfo& buffer_info, uint32_t count = 1) const;

    void UpdateDescriptors(uint32_t index, const std::vector<VkWriteDescriptorSet>& descriptor_writes);

  private:
    std::vector<VkDescriptorSet>               m_descriptor_sets;
    const std::map<uint32_t, VkDescriptorType> m_binding_types;
    const DescriptorPool&                      m_descriptor_pool;

    VkDescriptorType GetBindingType(uint32_t binding) const;
};
} // namespace Laurel
