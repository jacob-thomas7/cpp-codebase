#pragma once

#include "core/polymorphic/polyid.hpp"

namespace core
{
    class Event : public polymorphic::PolyID {
    
    protected:
        template <typename Derived> Event(Derived* derived) : PolyID::PolyID(derived) {}
    };
}