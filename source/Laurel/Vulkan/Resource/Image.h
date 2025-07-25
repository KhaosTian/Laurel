#pragma once

#include "Laurel/Vulkan/Vulkan.h"
#include <cstdint>

namespace Laurel {
class CommandPool;
class Device;
class Buffer;
class DeviceMemory;

class Image final {
  public:
    Image(Image&&) noexcept;
    Image(const Device& device, VkExtent2D extent, uint32_t mip_level, VkFormat format);
    Image(const Device& device, VkExtent2D extent, uint32_t mip_level, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage);
    ~Image();

    VkImage       handle() const { return m_handle; }
    const Device& device() const { return m_device; }
    VkExtent2D    extent() const { return m_extent; }
    VkFormat      format() const { return m_format; }

    DeviceMemory         AllocateMemory(VkMemoryPropertyFlags property) const;
    VkMemoryRequirements GetMemoryRequirements() const;

    void        CopyFrom(CommandPool& cmd_pool, const Buffer& buffer);
    void        TransitionImageLayout(CommandPool& cmd_pool, VkImageLayout layout);
    static bool HasStencilComponent(const VkFormat format);

  private:
    const Device&    m_device;
    VkImage          m_handle;
    const VkExtent2D m_extent;
    const VkFormat   m_format;
    VkImageLayout    m_image_layout;
};

} // namespace Laurel
