#pragma once

#include <stdexcept>

#include "core/system.hpp"

namespace core::systems
{
    class Window : public System
    {
        public:
        Window()
        {
            throw std::runtime_error("Couldn't make a Window");
        }
    };
}