#include "Laurel/Vulkan/Command/CommandPool.h"
#include "Laurel/Vulkan/Vulkan.h"
#include "Laurel/Vulkan/Command/CommandBuffers.h"
#include "Laurel/Vulkan/Core/Device.h"
#include <cstddef>
#include <cstdint>

namespace Laurel {
CommandBuffers::CommandBuffers(CommandPool& cmd_pool, uint32_t size): m_cmd_pool(cmd_pool) {
    VkCommandBufferAllocateInfo allocate_info = {};
    allocate_info.sType                       = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocate_info.commandPool                 = m_cmd_pool.handle();
    allocate_info.level                       = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocate_info.commandBufferCount          = size;

    m_cmds.resize(size);

    Check(vkAllocateCommandBuffers(cmd_pool.device().handle(), &allocate_info, m_cmds.data()), "allocate command buffers");
}

CommandBuffers::~CommandBuffers() {
    if (m_cmds.empty()) return;
    vkFreeCommandBuffers(m_cmd_pool.device().handle(), m_cmd_pool.handle(), static_cast<uint32_t>(m_cmds.size()), m_cmds.data());
    m_cmds.clear();
}

VkCommandBuffer CommandBuffers::Begin(size_t i) {
    VkCommandBufferBeginInfo info = {};
    info.sType                    = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    info.flags                    = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
    info.pInheritanceInfo         = nullptr;

    Check(vkBeginCommandBuffer(m_cmds[i], &info), "beigin recording command buffer");

    return m_cmds[i];
}

void CommandBuffers::End(size_t i) {
    Check(vkEndCommandBuffer(m_cmds[i]), "record command buffer");
}

} // namespace Laurel
