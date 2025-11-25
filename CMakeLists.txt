# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.1
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

# Options
include("cmake/options.cmake")

# Dependencies
include("cmake/dependencies.cmake")

# Core Library
add_library(core
    src/application.cpp

    src/systems/metadata.cpp
    src/systems/window.cpp
    src/systems/runtime.cpp

    src/polymorphic/polymanager.cpp
)

target_link_libraries(core SDL3::SDL3)
target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${SDL3_SOURCE_DIR}/include
)

# Examples
if(CODEBASE_BUILD_EXAMPLES)
    add_subdirectory("examples")
endif()
