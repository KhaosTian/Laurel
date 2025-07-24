#pragma once

#include <GLFW/glfw3.h>
#include "Laurel/Vulkan/Vulkan.h"
#include <functional>

namespace Vulkan {
struct WindowConfig {
    uint32_t    width;
    uint32_t    height;
    std::string title;
    bool        is_fullscreen;
    bool        enable_resize;
};

class Window final {
  public:
    Window(Window&&) = delete;
    explicit Window(const WindowConfig& config);
    ~Window();

    GLFWwindow*         handle() const { return handle_; }
    const WindowConfig& config() const { return config_; }

    VkExtent2D               getWindowSize() const;
    std::vector<const char*> getRequiredInstanceExtensions() const;

    void pollEvents() const;
    void waitEvents() const;
    bool shouldClose() const;

  private:
    WindowConfig config_;
    GLFWwindow*  handle_ {};
};

} // namespace Vulkan
