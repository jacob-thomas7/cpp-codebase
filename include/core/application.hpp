#pragma once

#include <memory>
#include <optional>
#include <vector>
#include <utility>

#include "core/event.hpp"
#include "core/polymorphic/polymanager.hpp"


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
            auto search_id = polymorphic::PolyManager::id<T>();
            for (auto& pair : systems) {
                if (pair.first == search_id) {
                    return std::make_optional<std::reference_wrapper<T>>(*static_cast<T*>(pair.second.get()));
                }
            }
            return std::nullopt;
        }
    
        //! \brief Registers a core::System to be managed by the application
        //! \details Uses perfect forwarding to construct a class derived from core::System
        //! and own it via a std::unique_ptr.
        template<typename T, typename... Args> requires(std::is_base_of_v<System, T>)
        T& register_system(Args&&... args)
        {
            systems.emplace_back(polymorphic::PolyManager::id<T>(), std::make_unique<T>(*this, std::forward<Args>(args)...));
            return get_system<T>().value().get();
        }
        
        template<typename T> requires(std::is_base_of_v<Event, T>)
        void dispatch_event(T& event)
        {
            for (auto iter = systems.rbegin(); iter != systems.rend(); iter++) {
                std::cout << iter->first << std::endl;
                if (iter->second->handle_event(event)) {
                    break;
                }
            }
        }

    private:
        std::vector<std::pair<polymorphic::polymorphic_id_t, std::unique_ptr<System>>> systems;
    };
}