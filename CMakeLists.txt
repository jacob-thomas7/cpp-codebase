# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(core
    VERSION 0.0.4
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase-core
)

# Options
set(CORE_STATIC ON CACHE BOOL "Build the core library as a static library")
set(CORE_SHARED OFF CACHE BOOL "Build the core library as a shared library")

function(create_target lib_type)
    string(TOLOWER "${PROJECT_NAME}-${lib_type}" TARGET_NAME)

    set(SRC "${core_SOURCE_DIR}/src/${PROJECT_NAME}")

    add_library(${TARGET_NAME} ${lib_type}
        ${SRC}/application.cpp
        ${SRC}/polymorphic.cpp
        ${SRC}/system.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        ${core_SOURCE_DIR}/include
    )

    add_library(codebase::${TARGET_NAME} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(CORE_SHARED)
    create_target(SHARED)
endif()

if(CORE_STATIC)
    create_target(STATIC)
endif()

# Make sure codebase::core exists, default to static if both were created
if(TARGET ${PROJECT_NAME}-static)
    add_library(codebase::${PROJECT_NAME} ALIAS ${PROJECT_NAME}-static)
elseif(TARGET core-shared)
    add_library(codebase::${PROJECT_NAME} ALIAS ${PROJECT_NAME}-shared)
else()
    message(WARNING "codebase::${PROJECT_NAME} was not created because neither CORE_SHARED nor CORE_STATIC were set")
endif()