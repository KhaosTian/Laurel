#pragma once

#include <memory>

#include "Laurel/Core/Application.h"
#include "Laurel/Core/Assert.h"

extern Laurel::Application* Laurel::CreateApplication(int argc, char** argv);

int main(int argc, char** argv) {
    
    Laurel::Log::Init();
    auto app = Laurel::CreateApplication(argc, argv);
    LR_CORE_ASSERT(app, "Failed to create application instance");
    app->Run();
    delete app;
    Laurel::Log::Shutdown();
    
    return 0;
}