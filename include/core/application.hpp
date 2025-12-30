#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <utility>
#include <queue>
#include <chrono>

#include "core/event.hpp"
#include "core/polymorphic.hpp"
#include "core/system.hpp"

namespace core
{
    class System;
    
    //! \brief Maintainer of all core::Systems.
    class Application
    {
        public:
        //! \brief Returns a core::System if it was registered
        //! \details Returns an optional reference to a core::System of the type specefied
        //! by T.
        template<typename T> requires(std::is_base_of_v<System, T>)
        std::optional<std::reference_wrapper<T>> get_system()
        {
            auto search_id = PolyManager::id<T>();
            for (auto& system : systems) {
                if (system->id == search_id) {
                    return std::make_optional<std::reference_wrapper<T>>(*static_cast<T*>(system.get()));
                }
            }
            return std::nullopt;
        }
    
        //! \brief Registers a core::System to be managed by the application
        //! \details Uses perfect forwarding to construct a class derived from core::System
        //! and own it via a std::unique_ptr.
        template<typename T, typename... Args> requires(std::is_base_of_v<System, T>)
        void register_system(Args&&... args)
        {
            systems.emplace_back(std::make_unique<T>(*this, std::forward<Args>(args)...));
        }
        
        template<typename DurationT, typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event(DurationT delay, Args&&... args)
        {
            if (!running) return;

            event_queue.emplace_back(
                std::chrono::system_clock::now() + delay,
                std::make_unique<EventT>(std::forward<Args>(args)...)
            );
        }

        template<typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event_ms(std::chrono::milliseconds delay, Args&&... args)
        {
            queue_event<std::chrono::milliseconds, EventT>(delay, std::forward<Args>(args)...);
        }

        template<typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event(Args&&... args)
        {
            queue_event<std::chrono::milliseconds, EventT>(0, std::forward<Args>(args)...);
        }

        template<typename T> requires(std::is_base_of_v<Event, T>)
        void dispatch_event(T& event)
        {
            // if (!running) return;

            // for (auto iter = systems.rbegin(); iter != systems.rend(); iter++) {
            //     if (iter->second->handle_event(event)) {
            //         break;
            //     }
            // }
        }
        
        void loop();
        void quit();

        private:
        std::vector<std::unique_ptr<System>> systems;
        
        std::vector<std::pair<
            std::chrono::time_point<std::chrono::system_clock>,
            std::unique_ptr<Event>
        >> event_queue;

        bool running = true;
    };
}

#include "core/system.tpp"