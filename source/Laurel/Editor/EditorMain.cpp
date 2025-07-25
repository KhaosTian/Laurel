#include "pch.h"

#include "Laurel/Core/Log.h"
#include "Laurel/Core/Assert.h"
#include "EditorMain.h"

std::unique_ptr<Laurel::IApplication> Laurel::CreateApplication(Laurel::ApplicationConfig& config) {
    return std::make_unique<LaurelEditorApplication>(config);
}

LaurelEditorApplication::LaurelEditorApplication(Laurel::ApplicationConfig& config): Laurel::IApplication(config) {
}

void LaurelEditorApplication::OnInit() {
}

void LaurelEditorApplication::OnTick(double delta_seconds) {
}

void LaurelEditorApplication::OnDestroy() {
}

bool LaurelEditorApplication::OnKey(int key, int scancode, int action, int mods) {
    return false;
}

bool LaurelEditorApplication::OnCursorPosition(double xpos, double ypos) {
    return false;
}

bool LaurelEditorApplication::OnMouseButton(int button, int action, int mods) {
    return false;
}

bool LaurelEditorApplication::OnScroll(double xoffset, double yoffset) {
    return false;
}
