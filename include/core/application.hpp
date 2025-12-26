#pragma once

#include <memory>
#include <optional>

#include "core/polymorphic/polymanager.hpp"

namespace core
{
    class System;

    class Application
    {
    public:
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
    
        //! \brief Registers a core::System to be managed by the application
        //! \details Uses perfect forwarding to construct a class derived from core::System
        //! and own it via a std::unique_ptr.
        template<typename T, typename... Args> requires(std::is_base_of_v<System, T>)
        T& register_system(Args&&... args)
        {
            systems.emplace(polymorphic::PolyManager::id<T>(), std::make_unique<T>(*this, std::forward<Args>(args)...));
            return get_system<T>().value().get();
        }
        
    private:
        std::unordered_multimap<polymorphic::polymorphic_id_t, std::unique_ptr<System>> systems;
    };
}