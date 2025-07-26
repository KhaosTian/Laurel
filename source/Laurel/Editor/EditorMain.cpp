#include "pch.h"

#include "Laurel/EntryPoint.h"

#include "EditorMain.h"

EditorApp::EditorApp(Laurel::ApplicationDesc& desc): IApplication(desc) {
}

void EditorApp::onInit() {
    LR_INFO("onInit called for EditorApp");
}

void EditorApp::onTick() {
}

void EditorApp::onShutdown() {
}

bool EditorApp::onKey(int key, int scancode, int action, int mods) {
      return false;
}

bool EditorApp::onCursorPosition(double pos_x, double pos_y) {
    return false;
}

bool EditorApp::onMouseButton(int button, int action, int mods) {
    return false;
}

bool EditorApp::onScroll(double offset_x, double offset_y) {
    return false;
}

int main(int argc, char** argv) {
    return LaurelMain<EditorApp>(argc, argv);
}