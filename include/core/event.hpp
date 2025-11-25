#pragma once

#include "core/polymorphic/polyid.hpp"

namespace core
{
    //! \brief Base class for Event system
    class Event : public polymorphic::PolyID {
    protected:
        //! \brief Initializes a polymorphic ID on the class
        template <typename Derived> Event(Derived* derived) : PolyID::PolyID(derived) {}
    };
}