#pragma once

#include <memory>
#include <stdexcept>

#include <SDL3/SDL.h>
#include "core/systems/metadata.hpp"
#include "core/dependency.hpp"
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
        void update(events::Update& event);
    private:
        Application& app;
        Metadata& metadata;
        SDL_Window* window;
    };
}