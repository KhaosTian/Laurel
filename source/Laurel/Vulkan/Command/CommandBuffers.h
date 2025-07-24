#pragma once

#include "Laurel/Vulkan/Command/CommandPool.h"
#include "Laurel/Vulkan/Vulkan.h"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace Laurel {
class CommandPool;
class CommandBuffers final {
  public:
    CommandBuffers(CommandBuffers&&) = delete;
    CommandBuffers(CommandPool& cmd_pool, uint32_t size);
    ~CommandBuffers();

    uint32_t         size() const { return static_cast<uint32_t>(m_cmds.size()); }
    VkCommandBuffer& operator[](size_t i) { return m_cmds[i]; }

    VkCommandBuffer Begin(size_t i);
    void            End(size_t i);

  private:
    std::vector<VkCommandBuffer> m_cmds;
    const CommandPool&           m_cmd_pool;
};
} // namespace Laurel
