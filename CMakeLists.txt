# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(
    CROTALE_CORE
    VERSION 0.0.6
    LANGUAGES CXX
)

# Options
set(CROTALE_CORE_STATIC ON CACHE BOOL "Build the core library as a static library")
set(CROTALE_CORE_SHARED OFF CACHE BOOL "Build the core library as a shared library")

function(create_target lib_type)
    string(TOLOWER "crotale_core-${lib_type}" TARGET_NAME)
    string(TOLOWER "core-${lib_type}" TARGET_NAME_SHORT)

    set(SRC "${CROTALE_CORE_SOURCE_DIR}/src/core")
    
    add_library(${TARGET_NAME} ${lib_type}
        "${SRC}/application.cpp"
        "${SRC}/polymorphic.cpp"
        "${SRC}/system.cpp"
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        "${CROTALE_CORE_SOURCE_DIR}/include/"
    )

    add_library(crotale::${TARGET_NAME_SHORT} ALIAS ${TARGET_NAME})
endfunction()

# Create library
if(CROTALE_CORE_SHARED)
    create_target(SHARED)
endif()

if(CROTALE_CORE_STATIC)
    create_target(STATIC)
endif()

# Make sure the default target exists, default to static if both were created
if(TARGET crotale_core-static)
    add_library(crotale::core ALIAS crotale_core-static)
elseif(TARGET crotale_core-shared)
    add_library(crotale::core ALIAS crotale_core-shared)
else()
    message(WARNING "crotale::core was not created because neither CROTALE_CORE_STATIC nor CROTALE_CORE_SHARED were set")
endif()