#include "core/system.hpp"

namespace core
{
    void System::start(Event& event)
    {

    }

    void System::add_event_listener(std::string_view event_name, std::function<void(System*, Event&)> callback)
    {
        event_listeners.insert({ event_name, callback });
    }

    void System::on_event(core::Event& event)
    {
        if (event_listeners.contains(event.id())) {
            auto callback = event_listeners.at(event.id());
            
            callback(this, event);
        }
    }
}