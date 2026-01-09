#include "core/polymorphic.hpp"

namespace crotale::core
{
    PolyManager& PolyManager::get_instance()
    {
        static PolyManager instance;
        return instance;
    }
}