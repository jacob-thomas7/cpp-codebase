#pragma once

#include <functional>
#include <string>
#include <unordered_map>

#include "core/event.hpp"

namespace core
{
    enum class SystemStatus
    {
        active,
        suspended
    };

    class System
    {
        std::unordered_map<std::string_view, std::function<void(System*, Event&)>> event_listeners;

        public:
        System() {}
        void add_event_listener(std::string_view event_name, std::function<void(System*, Event&)> callback);
        void on_event(core::Event& event);

        void start(core::Event& event);
    };
}