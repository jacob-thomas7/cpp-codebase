#include "core/system.hpp"

namespace crotale::core
{
    void System::handle_event(Event& event)
    {
        for (auto& handler : event_handlers) {
            if (handler.first == event.id) {
                handler.second(this, event);
            }
        }
    }
}