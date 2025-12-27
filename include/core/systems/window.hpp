#pragma once

#include <cstdint>
#include <stdexcept>

#include <SDL3/SDL.h>

#include "core/system.hpp"
#include "core/application.hpp"
#include "core/systems/metadata.hpp"

namespace core::systems
{
    class Window : public System
    {
    public:
        Window(Application& application, uint8_t frame_rate = 60);
    
        std::weak_ptr<SDL_Renderer> get_renderer();

        bool on_start(events::Start& event);
        bool on_update(events::Update& event);

    private:
        Metadata& metadata;
        std::shared_ptr<SDL_Window> window;
        std::shared_ptr<SDL_Renderer> renderer;
        uint8_t frame_rate;
    };
}