# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.2
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

# Options
#include("cmake/options.cmake")

# Dependencies
# set(SDL_STATIC ON)
# set(SDL_SHARED OFF)
# include(FetchContent)
# FetchContent_Declare(
#     sdl3
#     GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
#     GIT_TAG        "release-3.2.24"
#     FIND_PACKAGE_ARGS NAMES SDL3
# )
# FetchContent_MakeAvailable(sdl3)

# Core Library
# add_library(core
    # src/application.cpp
    # #src/system.cpp

    # src/systems/metadata.cpp
    # src/systems/window.cpp

    # src/polymorphic/polymanager.cpp
# )
# target_link_libraries(core SDL3::SDL3)
# target_include_directories(core PUBLIC
#     ${PROJECT_SOURCE_DIR}/include
#     ${SDL3_SOURCE_DIR}/include
# )

# Examples
# if(CODEBASE_BUILD_EXAMPLES)
    add_executable(cpp-codebase-example1
        examples/example1.cpp
    )
    
    target_include_directories(cpp-codebase-example1 PUBLIC
        include
    )

    # target_link_libraries(cpp-codebase-example1 PUBLIC core)
# endif()
