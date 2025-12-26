#pragma once

#include "core/application.hpp"
#include "core/system.hpp"
#include "core/systems/metadata.hpp"

#include <iostream>

namespace core::systems
{
    class Window : public System
    {
    public:
        Window(Application& application) : System(application), metadata(require<Metadata>()) {
            std::cout << metadata.name << " From Window, Version" << std::endl;
        }
    
    private:
        Metadata& metadata;
    };
}