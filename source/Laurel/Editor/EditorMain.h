#pragma once

#include "Laurel.h"

class EditorApp final: public Laurel::IApplication {
    LR_NON_COPIABLE(EditorApp)
  public:
    explicit EditorApp(Laurel::ApplicationDesc& desc);
    ~EditorApp() override = default;
    void OnInit() override;
    void OnTick() override;
    void OnShutdown() override;
    bool OnKey(int key, int scancode, int action, int mods) override;
    bool OnCursorPosition(double pos_x, double pos_y) override;
    bool OnMouseButton(int button, int action, int mods) override;
    bool OnScroll(double offset_x, double offset_y) override;
};