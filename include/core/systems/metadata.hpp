#pragma once

#include <string>
#include <iostream>
#include <functional>

#include "core/system.hpp"

namespace core::systems
{
    struct Version
    {
        uint8_t version_major;
        uint8_t version_minor;
        uint8_t version_patch;
    };

    std::ostream& operator<<(std::ostream& os, const systems::Version& version)
    {
        os << (int) version.version_major << '.' << (int) version.version_minor << '.' << (int) version.version_patch;
        return os;
    }

    class Metadata : public System
    {
        public:
        const std::string name;
        const std::string description;
        const Version version;
        
        Metadata(
            const std::string_view name = "Application",
            const std::string_view description = "",
            const Version version = { 1, 0, 0 }
        ) : 
            name(name),
            description(description),
            version(version)
        { }
    };
}