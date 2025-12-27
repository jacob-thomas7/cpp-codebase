#include <iostream>

#include <SDL3/SDL.h>

#include "core/application.hpp"
#include "core/systems/metadata.hpp"
#include "core/systems/window.hpp"
#include "core/events/runtime.hpp"

using namespace core;

class Game : public System
{
public:
    Game(Application& application) : System(this, application), window(require<systems::Window>()) {
        add_event_handler(&Game::on_update);
    }

    bool on_update(events::Update& event)
    {
        auto renderer = window.get_renderer().lock().get();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &box);
        box.x += 1;
        box.y += 1;
        return false;
    };

private:
    systems::Window& window;
    SDL_FRect box = {50, 50, 100, 100};
};


using namespace std::chrono_literals;

int main()
{
    Application app;
    app.register_system<systems::Metadata>("My App", systems::Version {0, 0, 1});
    app.register_system<systems::Window>();
    app.register_system<Game>();
    
    app.queue_event<std::chrono::seconds, events::Start>(0s);

    app.loop();
}