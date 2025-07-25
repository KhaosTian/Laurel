#pragma once

#include <memory>

#include "Laurel/Core/Application.h"
#include "Laurel/Core/Assert.h"

extern std::unique_ptr<Laurel::IApplication> Laurel::CreateApplication(Laurel::ApplicationConfig& config);

int main(int argc, char** argv) {
    Laurel::ApplicationConfig config {};
    config.name   = "Laurel Application";
    config.width  = 1280;
    config.height = 720;

    auto app = CreateApplication(config);
    LR_CORE_ASSERT(app != nullptr, "Failed to create application instance");
    app->Run();
    app->Shutdown();
    return 0;
}