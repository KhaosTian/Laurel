#include "Core/Log.h"
#include "Core/Assert.h"
int main() {
    LR::Log::init();
    LR_CORE_INFO("Laurel Engine Initialized");
    LR_ASSERT(false, "This is a test assertion");
    return 0;
}