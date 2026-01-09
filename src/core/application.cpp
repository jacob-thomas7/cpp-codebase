#include <stdexcept>
#include "core/application.hpp"
#include <iostream>
namespace crotale::core
{
    Application* Application::instance = nullptr;

    Application::Application()
    {
        if (instance != nullptr) {
            throw std::runtime_error("Only one application may be initialized at once.");
        }

        instance = this;
    }

    Application::~Application()
    {
        instance = nullptr;
    }

    Application& Application::get_instance()
    {
        if (instance == nullptr) {
            throw std::runtime_error("Attempted to call Application::get_instance() without initilizing an Application");
        }
        return *instance;
    }

    void Application::loop()
    {
        while (running) {
            for (auto iter = event_queue.begin(); iter != event_queue.end(); ) {
                auto& pair = *iter;
                if (pair.first <= std::chrono::system_clock::now()) {
                    std::unique_ptr<Event> event_ptr = std::move(pair.second);
                    Event& event = *event_ptr.get();

                    iter = event_queue.erase(iter);

                    for (auto& system : systems) {
                        system->handle_event(event);
                        if (event.handled) break;
                    }
                } else {
                    ++iter;
                }
            }
        }
    }

    void Application::quit()
    {
        running = false;
    }
}