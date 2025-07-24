#include "Laurel/Core/Log.h"
#include "Laurel/Core/Assert.h"
#include "EditorMain.h"

int main() {
    Laurel::Log::Init();
    LR_INFO("Laurel Engine Initialized");
    int error = 1;

    std::string description = "This is a test error";

    LR_ASSERT(false, "This is a test assertion");
    return 1;
}

LaurelEditorApplication::LaurelEditorApplication(Laurel::WindowConfig& config) {
}

void LaurelEditorApplication::OnInit() {
}

void LaurelEditorApplication::OnTick(double delta_seconds) {
}
