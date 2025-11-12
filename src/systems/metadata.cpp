#include "core/systems/metadata.hpp"

namespace core::systems
{
    std::ostream& operator<<(std::ostream& os, const Version& version)
    {
        return os << (int) version.version_major << '.' << (int) version.version_minor << '.' << (int) version.version_patch;
    }
}