#include "pch.h"

#include "Laurel/Core/Application.h"

namespace Laurel {
void IApplication::Run() {
    OnInit();
    while (true) {
        ProcessEvents();
        OnTick();
    }
    OnShutdown();
}

void IApplication::ProcessEvents() {
}
    

}