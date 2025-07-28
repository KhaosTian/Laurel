#pragma once

#include <memory>

#include "Laurel/Core/Application.h"
#include "Laurel/Core/Assert.h"

template<typename T>
concept IsApplication = std::is_base_of_v<Laurel::IApplication, T>;

template<typename AppType> requires IsApplication<AppType>
int LaurelMain(int argc, char** argv) {
    Laurel::ApplicationDesc desc {};
    desc.name   = "Laurel Application";
    desc.width  = 1280;
    desc.height = 720;

    auto app = std::make_unique<AppType>(desc);
    {
        Laurel::Log::Init();
        LR_CORE_ASSERT(app != nullptr, "Failed to create application instance");
        app->Run();
        Laurel::Log::Shutdown();
    }

    return 0;
}