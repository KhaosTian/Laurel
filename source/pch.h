#pragma once

//  平台库
#ifdef LR_PLATFORM_WINDOWS
    #include <windows.h>
#endif

// 标准库
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <cstdarg>
#include <filesystem>
#include <fstream>
#include <functional>
#include <limits>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <filesystem>
#include <thread>
#include <source_location>

// 第三方库
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>

// 内部头文件
#include "Laurel/Core/Assert.h"
#include "Laurel/Core/Base.h"
#include "Laurel/Core/Log.h"
#include "Laurel/Core/Math.h"