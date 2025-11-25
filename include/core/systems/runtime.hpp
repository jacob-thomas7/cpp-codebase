#pragma once

#include "SDL3/SDL.h"

#include "core/application.hpp"
#include "core/system.hpp"
#include "core/events/start.hpp"
#include "core/events/update.hpp"

namespace core::systems
{
    class Runtime : public System
    {
    public:
        Runtime(Application& app, unsigned int max_fps);
        void start(events::Start& event);
        void update(events::Update& event);
    private:
        Application& app;
        unsigned int max_fps;
    };
}