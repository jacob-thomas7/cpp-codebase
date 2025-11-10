#pragma once

#include "core/polymorphic/polyid.hpp"
#include <type_traits>

namespace core
{
    //! \brief The basic unit of functionality
    //! \details A core::Application manages classes
    //! derived from System. A System may depend
    //! on other Systems, allowing separation of
    //! concerns as well as a form of "interproccess
    //! communication." Uses the curiously recurring
    //! template pattern.
    template<typename Derived>
    class System : public polymorphic::PolyID
    {
    protected:
        //! \brief Initializes a polymorphic ID on the class
        System() : PolyID::PolyID(*static_cast<Derived*>(this)) {}
    };
}