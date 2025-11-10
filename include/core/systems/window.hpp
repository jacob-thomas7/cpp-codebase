#pragma once

#include <SDL3/SDL.h>

#include "core/system.hpp"

namespace core::systems
{
    class Window : System<Window>
    {
    public:
        Window();
    private:
        SDL_Window* window;
    };
}