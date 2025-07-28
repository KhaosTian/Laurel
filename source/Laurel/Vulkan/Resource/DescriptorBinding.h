#pragma once

#include "Laurel/Vulkan/Vulkan.h"

namespace Laurel {
struct DescriptorBinding {
    uint32_t           binding; // 绑定位置
    uint32_t           descriptor_count; // 绑定数量
    VkDescriptorType   type; // 绑定类型
    VkShaderStageFlags stage; // 着色器阶段
};
} // namespace Laurel
