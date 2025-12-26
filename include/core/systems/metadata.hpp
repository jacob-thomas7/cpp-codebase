#pragma once

#include <ostream>
#include <string>
#include <stdint.h>

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
    std::ostream& operator<<(std::ostream& os, const Version& version);

    //! \brief A core::System which contains metadata about the application
    class Metadata : public System
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
            Application& application,
            std::string_view name = "Application",
            Version version = { 1, 0, 0 },
            std::string_view license = "All Rights Reserved"
        ) : System(application), name(name), version(version), license(license) {}
    };
}