#include "core/system.hpp"

namespace core
{
    bool System::handle_event(Event& event)
    {
        for (auto& handler : event_handlers) {
            if (handler.first == event.id) {
                if (handler.second(this, event)) {
                    return true;
                }
            }
        }
        return false;
    }
}