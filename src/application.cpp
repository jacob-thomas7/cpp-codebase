#include "core/application.hpp"

namespace core
{
    void Application::register_system(System& system)
    {
        systems.push_back(std::make_pair(SystemStatus::active, std::ref(system)));
    }

    void Application::on_event(Event& event)
    {
        for (auto system : systems) {
            if (system.first == SystemStatus::active) {
                system.second.get().on_event(event);
            }
        }
    }
}