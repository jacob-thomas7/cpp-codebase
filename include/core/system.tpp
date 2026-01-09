#pragma once

#include "core/system.hpp"

namespace crotale::core {
    template <typename T> requires(std::is_base_of_v<System, T>)
    System::System(T* derived_this) : application(Application::get_instance()), PolyID(derived_this) {}

    template <typename T> requires(std::is_base_of_v<System, T>)
    T& System::require()
    {
        auto system = application.get_system<T>();
        if (!system.has_value()) {
            throw MissingDependencyException(typeid(*this).name(), typeid(T).name());
        }
        return system.value().get();
    }

    template <typename SystemT, typename EventT>
    requires(std::is_base_of_v<SystemT, System>, std::is_base_of_v<Event, EventT>)
    void System::add_event_handler(void(SystemT::* handler)(EventT &))
    {
        std::function<void(SystemT*, EventT&)> handler_func = handler;
        auto callback = [handler_func](System* system, Event& event) {
            return handler_func(static_cast<SystemT*>(system), *static_cast<EventT*>(&event));
        };
        event_handlers.emplace(PolyManager::id<EventT>(), callback);
    }
}