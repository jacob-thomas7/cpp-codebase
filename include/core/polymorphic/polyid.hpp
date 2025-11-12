#pragma once

#include "core/polymorphic/polymanager.hpp"

namespace core::polymorphic
{
    class PolyID
    {
    public:
        //! \brief Stores the polymorphic ID of derived classes
        //! \details Contains a core::polymorphic::polymorphic_id_t
        //! assigned by the core::polymorphic::PolyManager to
        //! classes which derive from it.
        //! Useful when working with polymorphism in such a way
        //! that it is difficult to get identity of a derived class
        //! when working with references or pointers to the base class.
        const polymorphic_id_t id;

    protected:
        //! \brief Constructor that uses the polymorphic ID as assigned
        //! by the core::polymorphic::PolyManager
        template <typename T>
        PolyID(T* assignee) : id(PolyManager::id<T>()) {}
    };
}