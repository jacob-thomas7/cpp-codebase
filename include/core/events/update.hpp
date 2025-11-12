#pragma once

#include "core/event.hpp"

namespace core::events
{
    class Update : public Event {
    public:
        Update() : Event(this) {}
    };
}