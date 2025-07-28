#pragma once

#include <optional>

#include <vulkan/vulkan.h>

namespace Laurel {

struct QueueFamilyIndices {
    std::optional<uint32_t> graphics;
    std::optional<uint32_t> present;
    std::optional<uint32_t> compute;

    bool IsComplete() const { return graphics.has_value() && present.has_value() && compute.has_value(); }
};
} // namespace Laurel