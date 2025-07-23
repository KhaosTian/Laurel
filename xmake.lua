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

target("LaurelRuntime")
    set_kind("static")
    set_pcheader("source/Runtime/pch.h")
    add_includedirs(include_dirs)
    add_files("source/Runtime/**.cpp")
    add_headerfiles("source/Runtime/**.h")
    add_linkdirs(link_dirs)
target_end()

target("LaurelEditor")
    set_kind("binary")

    add_deps("LaurelRuntime")
    add_includedirs(include_dirs)
    add_files("source/Editor/**.cpp")
    add_headerfiles("source/Editor/**.h")
    add_linkdirs(link_dirs)
target_end()