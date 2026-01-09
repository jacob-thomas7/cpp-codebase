#pragma once
#define CROTALE_CORE_APPLICATION_H_

#include <memory>
#include <optional>
#include <vector>
#include <utility>
#include <queue>
#include <chrono>

#include "core/event.hpp"
#include "core/polymorphic.hpp"
#include "core/system.hpp"

namespace crotale::core
{
    class System;
    
    //! \brief Maintainer of all core::Systems.
    class Application
    {
    public:
        Application();
        ~Application();
        Application(const Application&) = delete;
        Application(Application&&) = delete;

        //! \brief Returns the Application instance
        static Application& get_instance();

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
            systems.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }
        
        //! \brief Places an event into the event queue.
        //! \details Places an event at the back of the event queue, to be run
        //! after the specified amount of time.
        //! If multiple events are queued to run at the same time (or within the
        //! same window of time granulariy), the one queued first will be run first.
        template<typename DurationT, typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event(DurationT delay, Args&&... args)
        {
            if (!running) return;

            event_queue.emplace_back(
                std::chrono::system_clock::now() + delay,
                std::make_unique<EventT>(std::forward<Args>(args)...)
            );
        }

        //! \brief Queues an event to run as soon as possible.
        //! \details Places an event in the queue to be run as soon as possible.
        //! Effectively a shortcut for queue_event with zero delay.
        //! It does *not* run before events that were already queued to run.
        //! If this behavior is desired, see `Application::interrupt()`.
        template<typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event(Args&&... args)
        {
            using namespace std::chrono_literals;
            queue_event<std::chrono::milliseconds, EventT>(0ms, std::forward<Args>(args)...);
        }

        //! \brief Queues an event, in milliseconds.
        //! \details Shortcut for queue_event with DurationT = std::chrono::milliseconds.
        template<typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void queue_event_ms(std::chrono::milliseconds delay, Args&&... args)
        {
            queue_event<std::chrono::milliseconds, EventT>(delay, std::forward<Args>(args)...);
        }

        //! \brief Interrupts processing to process a new event.
        //! \details Interrupts will be handled before the currently
        //! running event has finished; once the interrupt is handled, regular
        //! queue processing will continue.
        //! \warning A circular dependency of interrupts can cause a stack overflow,
        //! as control will never return to the main event queue.
        template<typename EventT, typename... Args> requires(std::is_base_of_v<Event, EventT>)
        void interrupt(Args&&... args)
        {
            if (!running) return;
            EventT event(std::forward<Args>(args)...);
            
            for (auto& system : systems) {
                system->handle_event(event);
                if (event.handled) break;
            }
        }
        
        //! \brief Begins the event system processing.
        //! \details See queue_event for details of the queue system.
        void loop();

        //! \brief Stops the event system processing.
        //! \details Stops the event loop as soon as it is safe to do so.
        void quit();

    private:
        static Application* instance;

        std::vector<std::unique_ptr<System>> systems;
        
        std::vector<std::pair<
            std::chrono::time_point<std::chrono::system_clock>,
            std::unique_ptr<Event>
        >> event_queue;

        bool running = true;
    };
}

#include "core/system.tpp"