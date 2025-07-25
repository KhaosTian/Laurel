#pragma once

#include <vector>
#include <string>

#include "Laurel/Utils/NonCopyable.h"
#include "Laurel/Core/Math.h"

namespace Laurel {

struct WindowDesc {
    uint32_t    width;
    uint32_t    height;
    std::string title;
    bool        is_fullscreen;
    bool        enable_resize;
};

class Window: NonCopyable {
  public:
    Window(const WindowDesc& desc);
    ~Window();

    GLFWwindow*         handle() const { return m_handle; }
    const WindowDesc& config() const { return m_desc; }

    Vector2f                 getWindowSize() const;
    std::vector<const char*> getRequiredInstanceExtensions() const;

    void pollEvents() const;
    void waitEvents() const;
    bool shouldClose() const;

  private:
    WindowDesc m_desc;
    GLFWwindow*  m_handle {};
};

} // namespace Laurel
