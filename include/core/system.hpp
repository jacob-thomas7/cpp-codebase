#pragma once

#include <functional>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "core/event.hpp"
#include "core/polymorphic.hpp"

namespace crotale::core
{
    // Forward declaration to resolve circular dependency.
    // For this same reason, the implementation of System was moved into system.tpp
    // which is included by application.hpp
    class Application;

    //! \brief Exception for missing System dependencies.
    //! \details If the System's application does not have a System that is needed
    //! by another System, this exception should be used. 
    //! It is typically thrown by core::System::require<T>().
    class MissingDependencyException : public std::runtime_error
    {
    public:
        //! \brief Constructs the exception.
        //! \details Constructs the exception based on which class is missing the dependency
        //! (current) and what that missing dependency is (missing).
        MissingDependencyException(std::string current, std::string missing) :
            std::runtime_error(std::string("\"") + current + "\" is missing dependency \"" + missing + "\"") {}
    };

    class System : public PolyID
    {
    public:
        //! \brief Attempts to handle an event.
        //! \details Checks each of the System's event_handlers for one that handles events of type T;
        //! if any handler returns true—signifying the event was handled—the execution stops there.
        //! \param event The event to handle.
        //! \tparam T The type of the event to handle.
        //! \returns true if the event was handled.
        void handle_event(Event& event);
        
    protected:
        //! \brief Constructs a System with a reference to its owning Application.
        template <typename T> requires(std::is_base_of_v<System, T>)
        System(T* derived_this);
        
        //! \brief Ensures that the owning Application has a specific System.
        //! \throws a MissingDependencyException if the application does not have a System of the specified type.
        //! \tparam T The type, derived from core::System, to check for.
        template <typename T> requires(std::is_base_of_v<System, T>)
        T& require();

        //! \brief Adds an event handler.
        //! \details Adds a callback function to be called when an event of type EventT occurs.
        //! Works best with the following syntax: `add_event_handler(&MySystem::my_event_handler)`.
        //! \tparam EventT The type of Event to handle. Should be type-deduced.
        //! \tparam SystemT Should always be the type of the class itself, which is derived from System. Should be type-deduced. 
        //! \param handler The method to use as the handler.
        template <typename SystemT, typename EventT>
        requires(std::is_base_of_v<SystemT, System>, std::is_base_of_v<Event, EventT>)
        void add_event_handler(void(SystemT::* handler)(EventT&));

        //! \brief The owning application.
        Application& application;
        
    private:
        //! \brief Contains the event handlers.
        //! \details Assigned to by add_event_handler.
        std::unordered_multimap<
            polymorphic_id_t,
            std::function<void(System*, Event&)>
        > event_handlers;
    };
}

#ifndef CROTALE_CORE_APPLICATION_H_
    #include "core/application.hpp"
#endif