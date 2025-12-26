#pragma once

#include <functional>
#include <stdexcept>
#include <string>

#include "core/application.hpp"
#include "core/event.hpp"

namespace core
{
    class MissingDependencyException : public std::runtime_error
    {
    public:
        MissingDependencyException(std::string current, std::string missing) :
            std::runtime_error(std::string("\"") + current + "\" is missing dependency \"" + missing + "\"") {}
    };

    class System
    {
    public:
        template <typename T> requires(std::is_base_of_v<Event, T>)
        bool handle_event(T& event)
        {
            auto search_id = polymorphic::PolyManager::id<T>();
            for (auto& handler : event_handlers) {
                if (handler.first == search_id) {
                    if (handler.second(this, event)) {
                        return true;
                    }
                }
            }
            return false;
        }

    protected:
        System(Application& application) : application(application) {}
        template <typename T>
        T& require()
        {
            auto system = application.get_system<T>();
            if (!system.has_value()) {
                throw MissingDependencyException(typeid(this).name(), typeid(T).name());
            }
            return system.value();
        }

        template <typename SystemT, typename EventT>
        requires(std::is_base_of_v<SystemT, System>, std::is_base_of_v<Event, EventT>)
        void add_event_handler(bool (SystemT::* handler)(EventT &))
        {
            std::function<bool(SystemT*, EventT&)> handler_func = handler;
            auto callback = [handler_func](System* system, Event& event) {
                return handler_func(static_cast<SystemT*>(system), *static_cast<EventT*>(&event));
            };
            event_handlers.emplace(polymorphic::PolyManager::id<EventT>(), callback);
        }

    private:
        Application& application;
        std::unordered_multimap<
            polymorphic::polymorphic_id_t,
            std::function<bool(System*, Event&)>
        > event_handlers;
    };
}