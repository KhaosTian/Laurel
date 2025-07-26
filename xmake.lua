set_project("Laurel")
set_version("0.1.0")

set_arch("x64")
set_plat("windows")
set_toolchains("msvc")
set_languages("c++20")

add_rules("mode.debug", "mode.release")
add_rules("plugin.compile_commands.autoupdate", {outputdir = ".vscode"})
add_rules("plugin.vsxmake.autoupdate")

if is_mode("debug") then
    add_defines("LR_DEBUG")
elseif is_mode("release") then 
    add_defines("LR_RELEASE")
end

if is_plat("windows") then
    add_defines("LR_PLATFORM_WINDOWS")
end

local include_dirs= {
    "source",
    "external/glfw/include",
    "external/glm/include",
    "external/spdlog/include",
    "external/stb/include",
    "external/vulkan/include"
}

local link_dirs = {
    "external/glfw/lib-vc2022",
    "external/vulkan"
}

target("Laurel")
    set_kind("static")

    set_pcxxheader("source/pch.h")

    add_includedirs(include_dirs)
    add_linkdirs(link_dirs)

    add_files(
        "source/*.cpp",
        "source/Laurel/Core/**.cpp",
        "source/Laurel/Rhi/**.cpp"
    )
    add_headerfiles(
        "source/*.h",
        "source/Laurel/*.h",
        "source/Laurel/Core/**.h",
        "source/Laurel/Rhi/**.h"
    )
target_end()

target("LaurelEditor")
    set_kind("binary")

    add_deps("Laurel")
    add_includedirs(include_dirs)
    add_linkdirs(link_dirs)

    add_files("source/Laurel/Editor/**.cpp")
    add_headerfiles("source/Laurel/Editor/**.h")

target_end()