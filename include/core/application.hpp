#pragma once

#include <functional>
#include <unordered_map>
#include <memory>
#include <optional>

#include "core/polymorphic/polymanager.hpp"
#include "core/system.hpp"
#include "core/event.hpp"

namespace core
{
    //! \brief Container and state manager for an application
    class Application
    {
    public:
        //! \brief Registers a core::System to be managed by the application
        //! \details Uses perfect forwarding to construct a class derived from core::System
        //! and own it via a std::unique_ptr.
        template<typename T, typename... Args> requires(std::is_base_of_v<System, T>)
        T& register_system(Args&&... args)
        {
            systems.emplace(polymorphic::PolyManager::id<T>(), std::make_unique<T>(std::forward<Args>(args)...));
            return get_system<T>().value().get();
        }

        //! \brief Returns a core::System if it was registered
        //! \details Returns an optional reference to a core::System of the type specefied
        //! by T.
        template<typename T> requires(std::is_base_of_v<System, T>)
        std::optional<std::reference_wrapper<T>> get_system()
        {
            auto search = systems.find(polymorphic::PolyManager::id<T>());
            if (search == systems.end()) return std::nullopt;

            return std::make_optional<std::reference_wrapper<T>>(*static_cast<T*>(search->second.get()));
        }

        template<typename SystemT, typename EventT> requires(std::is_base_of_v<System, SystemT>, std::is_base_of_v<Event, EventT>)
        void add_event_listener(SystemT* instance, std::function<void(SystemT*, EventT& event)> handler) {
            auto func = [instance, handler](Event& event) {
                handler(instance, *static_cast<EventT*>(&event));
            };
            
            event_handlers.emplace(polymorphic::PolyManager::id<EventT>(), func);
            //std::function<void(Event&)> handler = std::bind(func, instance, std::placeholders::_1);
        }

        template <typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void dispatch_event(Args&&... args)
        {
            auto search = event_handlers.find(polymorphic::PolyManager::id<EventT>());
            if (search != event_handlers.end()){
                EventT event(std::forward<Args>(args)...);
                search->second(event);
            }
        }


        // void add_event_listener(systems::Window* instance, std::function<void(systems::Window*, events::Start&)> handler)
        // {
        //     auto func = [instance, handler](Event& event) {
        //         handler(instance, *static_cast<events::Start*>(&event));
        //     };

        //     event_handlers.emplace(polymorphic::PolyManager::id<events::Start>(), func);
        // }
    private:
        //! \brief Contains the polymorphic IDs of owned Systems
        std::unordered_multimap<polymorphic::polymorphic_id_t, std::unique_ptr<System>> systems;
        public:
        std::unordered_multimap<polymorphic::polymorphic_id_t, std::function<void(Event&)>> event_handlers;
    };
}