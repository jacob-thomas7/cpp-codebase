#pragma once

#include <vector>

#include "core/system.hpp"
#include "core/events/message.hpp"

namespace core::events
{
    template<typename T>// requires(std::is_base_of_v<Message, T>)
    class Topic
    {
    public:
        void publish(T& message)
        {
            for (System& system : subscribers)
            {
                system.handle_event<T>(message);
            }
        }

        static void subscribe(System& system)
        {
            subscribers.emplace_back(system);
        }

        //  template<typename T, typename... Args> requires(std::is_base_of_v<System, T>)
        // T& register_system(Args&&... args)
        // {
        //     systems.emplace(polymorphic::PolyManager::id<T>(), std::make_unique<T>(std::forward<Args>(args)...));
        //     return get_system<T>().value().get();
        // }
    private:
        static std::vector<std::reference_wrapper<System>> subscribers;
    };
}