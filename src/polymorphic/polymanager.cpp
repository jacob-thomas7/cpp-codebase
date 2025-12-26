#include "core/polymorphic/polymanager.hpp"

namespace core::polymorphic
{
    PolyManager& PolyManager::get_instance()
    {
        if (instance == NULL) {
            instance = new PolyManager;
        }
        return *instance;
    }
}