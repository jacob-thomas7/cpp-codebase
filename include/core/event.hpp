#pragma once

#include "core/polymorphic.hpp"

namespace crotale::core
{
    class Event : public PolyID
    {
    public:
        bool handled;
    protected:
        template <typename T> requires(std::is_base_of_v<Event, T>)
        Event(T* derived_this) : PolyID(derived_this), handled(false) {}
        
    };
}