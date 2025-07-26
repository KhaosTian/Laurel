#pragma once

#include <memory>
#include <string>

namespace Laurel {
struct ApplicationDesc {
    std::string name{ "Laurel Application" };
    int         width{ 1280 };
    int         height{ 720 };
    bool        is_fullscreen{ false };
    bool        enable_resize{ true };
};

class IApplication {
    LR_NON_COPIABLE(IApplication)
public:
    explicit IApplication(ApplicationDesc& desc) {}
    virtual ~IApplication() = default;

    void run();
    void processEvents();

    // 应用声明周期
    virtual void onInit() = 0;
    virtual void onTick() = 0;
    virtual void onShutdown() = 0;

    // 输入事件
    virtual bool onKey(int key, int scancode, int action, int mods) = 0;
    virtual bool onCursorPosition(double pos_x, double pos_y) = 0;
    virtual bool onMouseButton(int button, int action, int mods) = 0;
    virtual bool onScroll(double offset_x, double offset_y) = 0;
};
} // namespace Laurel