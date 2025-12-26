# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.2
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

# Options
include("cmake/options.cmake")
include("cmake/dependencies.cmake")

# Core Library
set(LIB_TYPE STATIC)
if(CORE_SHARED AND CORE_STATIC)
    message(FATAL_ERROR "Cannot use both a static and a shared library")
endif()
if((NOT CORE_SHARED) AND (NOT CORE_STATIC))
    message(FATAL_ERROR "Must build as either CORE_SHARED or CORE_STATIC")
endif()
if(CORE_SHARED)
    set(LIB_TYPE SHARED)
else()
    set(LIB_TYPE STATIC)
endif()


add_library(core ${LIB_TYPE}
    # src/application.cpp
    #src/system.cpp

    # src/systems/metadata.cpp
    # src/systems/window.cpp
    
    src/polymorphic/polymanager.cpp
)

target_include_directories(core PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Examples
if(CORE_BUILD_EXAMPLES)
    add_executable(cpp-codebase-example1
        examples/example1.cpp
    )
    
    target_include_directories(cpp-codebase-example1 PUBLIC
        include
    )

    target_link_libraries(cpp-codebase-example1 PUBLIC core)
endif()