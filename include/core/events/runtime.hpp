#pragma once

#include "core/event.hpp"

namespace core::events
{
    class Start : public Event {
    public:
        Start() : Event(this) {}
    };

    class Update : public Event {
    public:
        Update() : Event(this) {}
    };

    class Quit : public Event {
    public:
        Quit() : Event(this) {}
    };
}