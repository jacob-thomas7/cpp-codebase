#pragma once

#include <tuple>
#include <vector>

#include "core/system.hpp"

namespace core
{
    class Application
    {
        public: 
        void register_system(System& system);
        void on_event(Event& event);

        private:
        std::vector<std::pair<SystemStatus, std::reference_wrapper<System>>> systems; 
    };
}