#pragma once

namespace LR {

struct ApplicationDesc {
    const char* name   = "Laurel Application";
    int         width  = 1280;
    int         height = 720;
}

class Application {
  public:
    void Run();
    void Close();

    Application();
    virtual ~Application() = default;
};
} // namespace LR