#include "core/application.hpp"

namespace core
{
    void Application::loop()
    {
        while (running) {
            for (auto iter = event_queue.begin(); iter != event_queue.end(); ) {
                auto& pair = *iter;
                if (pair.first <= std::chrono::system_clock::now()) {
                    std::unique_ptr<Event> event = std::move(pair.second);
                    
                    iter = event_queue.erase(iter);

                    for (auto& system : systems) {
                        system->handle_event(*event.get());
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