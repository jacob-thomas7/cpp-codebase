#include <chrono>

#include "core/systems/window.hpp"

using namespace std::chrono_literals;

namespace core::systems
{
    Window::Window(Application& application, uint8_t frame_rate) :
        System(this, application), metadata(require<Metadata>()), frame_rate(frame_rate) {
        add_event_handler(&Window::on_start);
        add_event_handler(&Window::on_update);
    }

    std::weak_ptr<SDL_Renderer> Window::get_renderer()
    {
        return renderer;
    }

    bool Window::on_start(events::Start& event)
    {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            throw std::runtime_error(SDL_GetError());
        }

        window = std::shared_ptr<SDL_Window>(
            SDL_CreateWindow(metadata.name.data(), 400, 800, SDL_WINDOW_MAXIMIZED | SDL_WINDOW_RESIZABLE),
            SDL_DestroyWindow
        );
        if (window == NULL) {
            throw std::runtime_error(SDL_GetError());
        }

        renderer = std::shared_ptr<SDL_Renderer>(
            SDL_CreateRenderer(window.get(), NULL),
            SDL_DestroyRenderer
        );
        if (renderer == NULL) {
            throw std::runtime_error(SDL_GetError());
        }

        application.queue_event_ms<events::Update>(0ms);
        return false;
    }

    bool Window::on_update(events::Update& event)
    {
        SDL_Event poll_event;
        while (SDL_PollEvent(&poll_event)) {
            switch (poll_event.type) {
                case SDL_EVENT_QUIT:
                    application.quit();
                    break;
            }
        }
        
        SDL_RenderPresent(renderer.get());
        
        SDL_RenderClear(renderer.get());
        
        application.queue_event_ms<events::Update>(1000ms / frame_rate);

        return false;
    }
}