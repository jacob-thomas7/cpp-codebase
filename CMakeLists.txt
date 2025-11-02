cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.1
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

add_library(core
    src/application.cpp
    src/system.cpp
)
target_include_directories(core PUBLIC
    include
)

if(CODEBASE_BUILD_EXAMPLES)
    add_executable(cpp-codebase-example1
        examples/example1.cpp
    )
    
    target_include_directories(cpp-codebase-example1 PUBLIC
        include
    )

    target_link_libraries(cpp-codebase-example1 PUBLIC core)
endif()


# include(FetchContent)
# FetchContent_Declare(
#   sdl3
#   GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
#   GIT_TAG        "release-3.2.24"
#   FIND_PACKAGE_ARGS NAMES SDL3
# )
# FetchContent_MakeAvailable(sdl3)

# target_link_libraries(Test sdl3::SDL3-shared)