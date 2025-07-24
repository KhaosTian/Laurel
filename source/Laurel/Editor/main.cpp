#include "Laurel/Core/Log.h"
#include "Laurel/Core/Assert.h"

int main() {
    LR::Log::init();
    LR_INFO("Laurel Engine Initialized");
    int error = 1;

    std::string description = "This is a test error";

    LR_ASSERT(false, "This is a test assertion");
    return 1;
}