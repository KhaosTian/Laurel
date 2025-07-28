#pragma once

#include <vector>
#include <string>

#include "Laurel/Core/Math.h"

namespace Laurel {

struct WindowDesc {
    int         width;
    int         height;
    std::string title;
    bool        isFullscreen;
    bool        enableResize;
};

class Window {
    LR_NON_COPIABLE(Window)
  public:
    explicit Window(const WindowDesc& desc);
    ~Window();

    GLFWwindow*       GetHandle() const { return m_window; }
    const WindowDesc& GetDesc() const { return m_desc; }

    Vector2i                 GetWindowSize() const;
    std::vector<const char*> GetRequiredInstanceExtensions() const;

    void PollEvents() const;
    void WaitEvents() const;
    bool ShouldClose() const;

    std::function<void(int key, int scancode, int action, int mods)> onKey;
    std::function<void(double posX, double posY)>                    onCursorPosition;
    std::function<void(int button, int action, int mods)>            onMouseButton;
    std::function<void(double offsetX, double offsetY)>              onScroll;

  private:
    WindowDesc  m_desc;
    GLFWwindow* m_window {};
    bool        m_initialized { false };
};

} // namespace Laurel
