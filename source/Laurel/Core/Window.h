#pragma once

#include <vector>
#include <string>

#include "Laurel/Core/Math.h"

namespace Laurel {

struct WindowDesc {
    int         width;
    int         height;
    std::string title;
    bool        is_fullscreen;
    bool        enable_resize;
};

class Window {
    LR_NON_COPIABLE(Window)
  public:
    explicit Window(const WindowDesc& desc);
    ~Window();

    GLFWwindow*       handle() const { return m_window; }
    const WindowDesc& config() const { return m_desc; }

    Vector2i                        getWindowSize() const;
    static std::vector<const char*> getRequiredInstanceExtensions();

    void pollEvents() const;
    void waitEvents() const;
    bool shouldClose() const;

    std::function<void(int key, int scancode, int action, int mods)> on_key;
    std::function<void(double pos_x, double pos_y)> on_cursor_position;
    std::function<void(int button, int action, int mods)> on_mouse_button;
    std::function<void(double offset_x, double offset_y)> on_scroll;
    std::function<void(int path_count, const char* paths[])> on_drop_file;
    std::function<void(GLFWwindow* window, int focused)> on_focus;

  private:
    WindowDesc  m_desc;
    GLFWwindow* m_window {};
};

} // namespace Laurel
