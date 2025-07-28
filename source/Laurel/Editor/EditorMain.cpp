#include "pch.h"

#include "Laurel/EntryPoint.h"

#include "EditorMain.h"

EditorApp::EditorApp(Laurel::ApplicationDesc& desc): IApplication(desc) {
}

void EditorApp::OnInit() {
    LR_INFO("onInit called for EditorApp");
}

void EditorApp::OnTick() {
}

void EditorApp::OnShutdown() {
}

bool EditorApp::OnKey(int key, int scancode, int action, int mods) {
      return false;
}

bool EditorApp::OnCursorPosition(double pos_x, double pos_y) {
    return false;
}

bool EditorApp::OnMouseButton(int button, int action, int mods) {
    return false;
}

bool EditorApp::OnScroll(double offset_x, double offset_y) {
    return false;
}

int main(int argc, char** argv) {
    return LaurelMain<EditorApp>(argc, argv);
}