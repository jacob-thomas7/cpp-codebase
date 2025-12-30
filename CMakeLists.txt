# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.4
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

# Options
set(CORE_STATIC ON CACHE BOOL "Build the core library as a static library")
set(CORE_SHARED OFF CACHE BOOL "Build the core library as a shared library")

function(create_target lib_type)
    string(TOLOWER "core-${lib_type}" TARGET_NAME)

    add_library(${TARGET_NAME} ${lib_type}
        ${CORE_SOURCE_DIR}/src/core/*.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        include
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
if(TARGET core-static)
    add_library(codebase::core ALIAS core-static)
elseif(TARGET core-shared)
    add_library(codebase::core ALIAS core-shared)
else()
    message(WARNING "codebase::core was not created because neither CORE_SHARED nor CORE_STATIC were set")
endif()