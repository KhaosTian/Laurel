#include "Runtime/Core/Log.h"
#include "Runtime/Core/Assert.h"

int main() {
    LR::Log::init();
    LR_INFO("Laurel Engine Initialized");
    LR_ASSERT(false, "This is a test assertion");
    return 0;
}