#pragma once

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Laurel/Utils/NonCopyable.h"

namespace Laurel {
class Vector2f;

struct WindowConfig {
    uint32_t    width;
    uint32_t    height;
    std::string title;
    bool        is_fullscreen;
    bool        enable_resize;
};

class Window: NonCopyable {
  public:
    Window(const WindowConfig& config);
    ~Window();

    GLFWwindow*         handle() const { return m_handle; }
    const WindowConfig& config() const { return m_config; }

    Vector2f                 GetWindowSize() const;
    std::vector<const char*> GetRequiredInstanceExtensions() const;

    void PollEvents() const;
    void WaitEvents() const;
    bool ShouldClose() const;

  private:
    WindowConfig m_config;
    GLFWwindow*  m_handle {};
};

} // namespace Laurel
