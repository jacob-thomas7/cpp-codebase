#pragma once

#include "core/polymorphic.hpp"

namespace core
{
    class Event : public PolyID
    {
    protected:
        template <typename T> requires(std::is_base_of_v<Event, T>)
        Event(T* derived_this) : PolyID(derived_this) {}
    };
}