#pragma once

#include <memory>
#include <string>

#include "Laurel/Core/Base.h"
#include "Laurel/Core/Window.h"

namespace Laurel {
struct ApplicationDesc {
    std::string name { "Laurel Application" };
    int         width { 1280 };
    int         height { 720 };
    bool        isFullscreen { false };
    bool        enableResize { false };
};

class Application {
    LR_NON_COPIABLE(Application)
  public:
    explicit Application(const ApplicationDesc& desc);
    virtual ~Application() = default;

    void Run();
    void ProcessEvents();

    // 应用声明周期
    virtual void OnInit()     = 0;
    virtual void OnTick()     = 0;
    virtual void OnShutdown() = 0;

    // 输入事件
    virtual bool OnKey(int key, int scancode, int action, int mods) = 0;
    virtual bool OnCursorPosition(double pos_x, double pos_y)       = 0;
    virtual bool OnMouseButton(int button, int action, int mods)    = 0;
    virtual bool OnScroll(double offset_x, double offset_y)         = 0;

    Window& GetWindow() const { return *m_window; }
  protected:
    std::unique_ptr<Window> m_window;
};

// 创建应用
Application* CreateApplication(int argc, char** argv);
} // namespace Laurel