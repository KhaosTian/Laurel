#include <Laurel.h>
#include <Laurel/EntryPoint.h>
#include <Laurel/Core/Window.h>
#include <Laurel/Rhi/RhiContext.h>
#include <Laurel/Rhi/RhiUtils.h>

class EditorApp final: public Laurel::Application {
    LR_NON_COPIABLE(EditorApp)
  public:
    explicit EditorApp(const Laurel::ApplicationDesc& desc);
    ~EditorApp() override = default;
    void OnInit() override;
    void OnTick() override;
    void OnShutdown() override;
    bool OnKey(int key, int scancode, int action, int mods) override;
    bool OnCursorPosition(double pos_x, double pos_y) override;
    bool OnMouseButton(int button, int action, int mods) override;
    bool OnScroll(double offset_x, double offset_y) override;
};

EditorApp::EditorApp(const Laurel::ApplicationDesc& desc): Application(desc) {
    Laurel::RhiContext rhiContext { GetWindow() };
}

void EditorApp::OnInit() {
    LR_INFO("onInit called for EditorApp");
}

void EditorApp::OnTick() {
}

void EditorApp::OnShutdown() {
}

bool EditorApp::OnKey(int key, int scancode, int action, int mods) {
    return false;
}

bool EditorApp::OnCursorPosition(double pos_x, double pos_y) {
    return false;
}

bool EditorApp::OnMouseButton(int button, int action, int mods) {
    return false;
}

bool EditorApp::OnScroll(double offset_x, double offset_y) {
    return false;
}

Laurel::Application* Laurel::CreateApplication(int argc, char** argv) {
    Laurel::ApplicationDesc desc {};
    desc.name         = "Laurel Editor";
    desc.width        = 1280;
    desc.height       = 720;
    desc.isFullscreen = false;
    desc.enableResize = false;
    return new EditorApp(desc);
}