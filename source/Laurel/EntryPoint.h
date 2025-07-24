#pragma once

#include "Laurel/Core/Applcation.h"

extern std::unique_ptr<Laurel::IApplication> Laurel::CreateApplication(WindowConfig& config);

namespace Laurel {
int Main(int argc, char** argv) {

}
}