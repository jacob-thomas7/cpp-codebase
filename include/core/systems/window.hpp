#pragma once

#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>
#include "core/systems/metadata.hpp"
#include "core/system.hpp"
#include "core/application.hpp"

#include "core/event.hpp"
#include "core/events/update.hpp"
#include <iostream>

namespace core::systems
{
    class Window : public System
    {
    public:
        //! \brief Constructs Metadata, supplying default values
        Window(Application& app, Metadata& metadata);
        //! \brief Event handler for core::events::Update 
        void update(events::Update& event);
        SDL_Window* window;
    private:
        Application& app;
        Metadata& metadata;
    };
}