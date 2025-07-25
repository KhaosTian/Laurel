#pragma once

#include "Laurel.h"

class LaurelEditorApplication: public Laurel::IApplication {
  public:
    LaurelEditorApplication(Laurel::ApplicationConfig& config);
    ~LaurelEditorApplication() override = default;
    void OnInit() override;
    void OnTick(double delta_seconds) override;
    void OnDestroy() override;
    bool OnKey(int key, int scancode, int action, int mods) override;
    bool OnCursorPosition(double xpos, double ypos) override;
    bool OnMouseButton(int button, int action, int mods) override;
    bool OnScroll(double xoffset, double yoffset) override;
};