#pragma once

#ifdef LR_PLATFORM_WINDOWS
    #include <windows.h>
#endif

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

#include "Laurel/Core/Assert.h"
#include "Laurel/Core/Base.h"
#include "Laurel/Core/Log.h"