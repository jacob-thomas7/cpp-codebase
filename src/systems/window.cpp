#include "core/systems/window.hpp"
#include "core/events/update.hpp"

namespace core::systems
{
    Window::Window(Application& app, Metadata& metadata) : System(this), app(app), metadata(metadata)
    {
        if (SDL_WasInit(SDL_INIT_VIDEO) == false) {
            if(SDL_Init(SDL_INIT_VIDEO) == false){
                throw std::runtime_error("Failure initializing SDL: " + std::string(SDL_GetError()));
            }
        }
        
        window = SDL_CreateWindow(metadata.name.data(), 500, 500, SDL_WINDOW_RESIZABLE);

        app.add_event_listener<Window, events::Update>(this, &Window::update);
    }

    void Window::update(events::Update& event)
    {
        std::cout << "Hello from update!";
        SDL_Event sdl_event;
            
        while(SDL_PollEvent(&sdl_event)){
            switch(sdl_event.type){
                case SDL_EVENT_QUIT:
                    exit(1);
            }
        }

        SDL_Delay(1000 / 60);
        app.dispatch_event<events::Update>();
    }
}