#pragma once

#include "Laurel/Core/Window.h"

namespace Laurel {

class IApplication {
  public:
    IApplication(WindowConfig& config) {}
    virtual ~IApplication() = default;

    // 应用声明周期
    virtual void OnInit()    = 0;
    virtual void OnTick(double delta_seconds) = 0;
    virtual void OnDestroy() = 0;

    // 输入事件
    virtual bool OnKey(int key, int scancode, int action, int mods) = 0;
    virtual bool OnCursorPosition(double xpos, double ypos)         = 0;
    virtual bool OnMouseButton(int button, int action, int mods)    = 0;
    virtual bool OnScroll(double xoffset, double yoffset) { return false; }
};

std::unique_ptr<IApplication> CreateApplication(WindowConfig& config);
} // namespace Laurel