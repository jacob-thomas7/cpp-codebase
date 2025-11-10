#pragma once

#include <ostream>
#include <string>

#include "core/system.hpp"

namespace core::systems
{
    //! \brief Information on Semantic Versioning
    struct Version
    {
        uint8_t version_major;
        uint8_t version_minor;
        uint8_t version_patch;
    };

    //! \brief Output stream formatter for core::systems::Version
    std::ostream& operator<<(std::ostream& os, const systems::Version& version)
    {
        os << (int) version.version_major << '.' << (int) version.version_minor << '.' << (int) version.version_patch;
        return os;
    }

    //! \brief A core::System which contains metadata about the application
    class Metadata : public System<Metadata>
    {
    public:
        //! \brief The name of the application
        //! \details Defaults to "Application."
        const std::string_view name;
        //! \brief The version of the application
        //! \details Defaults to 1.0.0.
        const Version version;
        //! \brief The application's license
        //! \details Defaults to "All Rights Reserved."
        const std::string_view license;

        //! \brief Constructs Metadata, supplying default values
        Metadata(
            std::string_view name = "Application",
            Version version = { 1, 0, 0 },
            std::string_view license = "All Rights Reserved"
        ) : name(name), version(version), license(license) {}
    };
}