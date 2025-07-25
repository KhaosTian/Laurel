#pragma once

#include <memory>
#include <string>

namespace Laurel {

struct ApplicationConfig {
    std::string name { "Laurel Application" };
    int         width { 1280 };
    int         height { 720 };
    bool        is_fullscreen { false };
    bool        enable_resize { true };
};

class IApplication {
  public:
    IApplication(ApplicationConfig& config) {}
    virtual ~IApplication() = default;

    void Run();
    void Shutdown();

    // 应用声明周期
    virtual void OnInit()                     = 0;
    virtual void OnTick(double delta_seconds) = 0;
    virtual void OnDestroy()                  = 0;

    // 输入事件
    virtual bool OnKey(int key, int scancode, int action, int mods) = 0;
    virtual bool OnCursorPosition(double xpos, double ypos)         = 0;
    virtual bool OnMouseButton(int button, int action, int mods)    = 0;
    virtual bool OnScroll(double xoffset, double yoffset) { return false; }
};

std::unique_ptr<IApplication> CreateApplication(ApplicationConfig& config);
} // namespace Laurel