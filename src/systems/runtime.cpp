#include "core/systems/runtime.hpp"

namespace core::systems
{
    Runtime::Runtime(Application& app, unsigned int max_fps = 60) : System(this), app(app), max_fps(max_fps) {
        app.add_event_handler<Runtime, events::Start>(this, &Runtime::start);
        app.add_event_handler<Runtime, events::Update>(this, &Runtime::update);
    }

    void Runtime::start(events::Start& event) {
        app.dispatch_event<events::Update>();
    }

    void Runtime::update(events::Update& event) {
        SDL_Delay(1000 / max_fps);
        app.dispatch_event<events::Update>();
    }
}