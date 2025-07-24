#pragma once

namespace LR {

class Application {
  public:
    void Run();
    void Close();

    Application();
    virtual ~Application() = default;

    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnShutdown() {}
};
} // namespace LR