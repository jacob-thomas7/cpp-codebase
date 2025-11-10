#pragma once

//! \namespace core::systems
//! \brief Collection of classes derived from core::System
//! \details Systems are the basic unit of functionality,
//! managed by a core::Application. Classes in this namespace
//! may be used in an application, and typically represent
//! commonly used features. Library users may also define
//! their own Systems by inheriting from System.

//! \file systems.hpp
//! \brief Header collection for the core::systems namespace

//! \file metadata.hpp
//! \brief Declaration of core::systems::Metadata
#include "core/systems/metadata.hpp"

//! \file window.hpp
//! \brief Declaration of core::systems::Window
//! \file window.cpp
//! \brief Definition of core::systems::Window
#include "core/systems/window.hpp"