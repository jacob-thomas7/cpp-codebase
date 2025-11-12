#pragma once

#include "core/polymorphic/polyid.hpp"

namespace core
{
    //! \brief The basic unit of functionality
    //! \details A core::Application manages classes
    //! derived from System. A System may depend
    //! on other Systems, allowing separation of
    //! concerns as well as a form of "interproccess
    //! communication."
    class System : public polymorphic::PolyID
    {
    protected:
        //! \brief Initializes a polymorphic ID on the class
        template <typename Derived> System(Derived* derived) : PolyID::PolyID(derived) {}
    };
}