#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

namespace core::polymorphic
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

            if (auto search = ids.find(typeid(T).raw_name()); search != ids.end()) {
                return search->second;
            }

            ids.emplace(typeid(T).raw_name(), ids.size());
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
}