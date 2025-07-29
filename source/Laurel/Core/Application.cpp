#include "pch.h"

#include "Laurel/Core/Application.h"

namespace Laurel {
Application::Application(const ApplicationDesc& desc) {
    WindowDesc windowDesc;
    windowDesc.width        = desc.width;
    windowDesc.height       = desc.height;
    windowDesc.title        = desc.name;
    windowDesc.isFullscreen = desc.isFullscreen;
    windowDesc.enableResize = desc.enableResize;

    m_window = std::make_unique<Window>(windowDesc);
}

void Application::Run() {
    OnInit();
    while (!m_window->ShouldClose()) {
        ProcessEvents();
        OnTick();
    }
    OnShutdown();
}

void Application::OnInit() {
}

void Application::ProcessEvents() {
}

void Application::OnTick() {
}

void Application::OnShutdown() {

}

} // namespace Laurel