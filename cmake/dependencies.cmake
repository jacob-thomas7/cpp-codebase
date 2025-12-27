set(SDL_STATIC ON)
set(SDL_SHARED OFF)
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY "https://github.com/libsdl-org/SDL.git"
    GIT_TAG        "release-3.2.24"
    FIND_PACKAGE_ARGS NAMES SDL3
)
FetchContent_MakeAvailable(SDL3)