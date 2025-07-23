#include "Laurel/Core/Log.h"
#include "Laurel/Core/Assert.h"

int main() {
    LR::Log::init();
    LR_INFO("Laurel Engine Initialized");
    LR_ASSERT(false, "This is a test assertion");
    return 0;
}