#pragma once

#include <functional>
#include <unordered_map>
#include <memory>
#include <optional>

#include "core/polymorphic/polymanager.hpp"
#include "core/system.hpp"
#include "core/event.hpp"

#include <iostream>

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

        //! \brief Registers a event handler
        //! \details Registers a function on an object of type SystemT which will be called
        //! when an event of EventT is dispatched.
        template<typename SystemT, typename EventT> requires(std::is_base_of_v<System, SystemT>, std::is_base_of_v<Event, EventT>)
        void add_event_handler(SystemT* instance, std::function<void(SystemT*, EventT& event)> handler) {
            auto func = [instance, handler](Event& event) {
                handler(instance, *static_cast<EventT*>(&event));
            };
            
            event_handlers.emplace(polymorphic::PolyManager::id<EventT>(), func);
        }

        //! \brief Dispatches a core::Event to event handlers
        //! \details Passes a core::Event of type EventT to each registered event handler
        //! that handles EventT.
        template <typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void dispatch_event(Args&&... args)
        {
            auto search = event_handlers.equal_range(polymorphic::PolyManager::id<EventT>());
            EventT event(std::forward<Args>(args)...);
            int count = 0;
            for (auto iter = search.first; iter != search.second; iter++) {
                std::cout << count++ << ", " << iter->first << "return 1?";
                //iter->second(event);
                std::cout <<"Return 2?" << std::endl;
            }
            std::cout << count << "hello?\n" << std::endl;
        }

    private:
        //! \brief Maps polymorphic IDs to owned Systems
        std::unordered_multimap<polymorphic::polymorphic_id_t, std::unique_ptr<System>> systems;
        //! \brief Maps polymorhpic IDs to event handlers of that type
        std::unordered_multimap<polymorphic::polymorphic_id_t, std::function<void(Event&)>> event_handlers;
    };
}