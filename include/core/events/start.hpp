#pragma once

#include "core/event.hpp"

namespace core::events
{
    class Start : public Event {
    public:
        Start() : Event(this) {}
    };
}