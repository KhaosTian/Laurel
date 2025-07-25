#include "pch.h"

#include "Laurel/Core/Application.h"

namespace Laurel {
void IApplication::run() {
    onInit();
    while (true) {
        processEvents();
        onTick();
    }
    onShutdown();
}

void IApplication::processEvents() {
}
    

}