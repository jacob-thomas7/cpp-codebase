#include <iostream>

#include "core/application.hpp"

#include "core/systems/metadata.hpp"
#include "core/systems/window.hpp"
#include "core/system.hpp"
#include "core/polymorphic/polymanager.hpp"
#include "core/events/update.hpp"
#include "core/systems/runtime.hpp"

#include "SDL3/SDL.h"

using namespace core;

class Game : public System
{
    systems::Window& window;
    SDL_Renderer* renderer;
public:
    void update(events::Update& event) {
        std::cout <<"Hello";
        // SDL_SetRenderDrawColor(renderer, 200, 200, 200, SDL_ALPHA_OPAQUE);
        // SDL_FRect rect = {50, 50, 100, 100};
        // SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // SDL_RenderFillRect(renderer, &rect);
        // SDL_RenderClear(renderer);
        // SDL_RenderPresent(renderer);
    }
    Game(Application& app, systems::Window& window) : System(this), window(window) {
        renderer = SDL_CreateRenderer(window.window, NULL);
        app.add_event_handler<Game, events::Update>(this, &Game::update);
        std::cout << "Make";
    }
};

int main()
{
    Application app;
    auto metadata = app.register_system<systems::Metadata>();
    auto window = app.register_system<systems::Window>(app, metadata);
    auto runtime = app.register_system<systems::Runtime>(app, 60);
    auto game = app.register_system<Game>(app, window);

    app.dispatch_event<events::Start>();
}