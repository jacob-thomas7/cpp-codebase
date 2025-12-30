#include "core/polymorphic.hpp"

namespace core
{
    PolyManager& PolyManager::get_instance()
    {
        if (instance == NULL) {
            instance = new PolyManager;
        }
        return *instance;
    }
}