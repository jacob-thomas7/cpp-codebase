# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(CORE
    VERSION 0.0.5
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase-core
)

string(TOLOWER "${PROJECT_NAME}" PROJECT_NAME_LOWER)

# Options
set(${PROJECT_NAME}_STATIC ON CACHE BOOL "Build the core library as a static library")
set(${PROJECT_NAME}_SHARED OFF CACHE BOOL "Build the core library as a shared library")

function(create_target lib_type)
    string(TOLOWER "${PROJECT_NAME_LOWER}-${lib_type}" TARGET_NAME)

    set(SRC "${${PROJECT_NAME}_SOURCE_DIR}/src/${PROJECT_NAME}")
    set(INC "${${PROJECT_NAME}_SOURCE_DIR}/src/${PROJECT_NAME}")

    add_library(${TARGET_NAME} ${lib_type}
        "${SRC}/application.cpp"
        "${SRC}/polymorphic.cpp"
        "${SRC}/system.cpp"
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        "${INC}/include/"
    )

    add_library(codebase::${TARGET_NAME} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(${PROJECT_NAME}_SHARED)
    create_target(SHARED)
endif()

if(${PROJECT_NAME}_STATIC)
    create_target(STATIC)
endif()

# Make sure the default target exists, default to static if both were created
if(TARGET ${PROJECT_NAME_LOWER}-static)
    add_library(codebase::${PROJECT_NAME_LOWER} ALIAS ${PROJECT_NAME_LOWER}-static)
elseif(TARGET ${PROJECT_NAME_UPPER}-shared)
    add_library(codebase::${PROJECT_NAME_LOWER} ALIAS ${PROJECT_NAME_LOWER}-shared)
else()
    message(WARNING "codebase::${PROJECT_NAME_LOWER} was not created because neither ${PROJECT_NAME}_STATIC nor ${PROJECT_NAME}_SHARED were set")
endif()