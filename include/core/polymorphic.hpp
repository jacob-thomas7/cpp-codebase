#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <typeinfo>

namespace core
{
    typedef uint64_t polymorphic_id_t;

    //! \brief Maintains and creates unique IDs for types
    class PolyManager
    {
    public:
        //! \brief Returns the polymorphic ID associated with type T
        template <typename T>
        static polymorphic_id_t id() {
            auto& ids = get_instance().ids;

            if (auto search = ids.find(typeid(T).name()); search != ids.end()) {
                return search->second;
            }

            ids.emplace(typeid(T).name(), ids.size());
            return ids.size() - 1;
        }

    private:
        //! \brief Maintains a singleton instance
        static inline PolyManager* instance = NULL;
        
        //! \brief Returns or creates the singleton instance
        static PolyManager& get_instance();

        //! \brief A map of type's raw names to their associated polymorphic ID
        std::unordered_map<std::string_view, polymorphic_id_t> ids = std::unordered_map<std::string_view, polymorphic_id_t>();
    };

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