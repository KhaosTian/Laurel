#pragma once

#include "Laurel.h"

class LaurelEditorApplication : public Laurel::IApplication {
  public:
    LaurelEditorApplication(Laurel::WindowConfig& config);
    ~LaurelEditorApplication() override = default;
    void OnInit() override;
    void OnTick(double delta_seconds) override;
    void OnDestroy() override {};
};