#pragma once

#include "Laurel.h"

class EditorApp final: public Laurel::IApplication {
    LR_NON_COPIABLE(EditorApp)
  public:
    explicit EditorApp(Laurel::ApplicationDesc& desc);
    ~EditorApp() override = default;
    void onInit() override;
    void onTick() override;
    void onShutdown() override;
    bool onKey(int key, int scancode, int action, int mods) override;
    bool onCursorPosition(double pos_x, double pos_y) override;
    bool onMouseButton(int button, int action, int mods) override;
    bool onScroll(double offset_x, double offset_y) override;
};