# Project Info
cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 20)

project(cpp-codebase
    VERSION 0.0.3
    LANGUAGES CXX
    HOMEPAGE_URL https://github.com/jacob-thomas7/cpp-codebase
)

set(CORE_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR} PARENT_SCOPE)

# Options
include("cmake/options.cmake")
# include("cmake/dependencies.cmake")

function(create_target lib_type)
    string(TOLOWER "core-${lib_type}" TARGET_NAME)

    add_library(${TARGET_NAME} ${lib_type}
        src/application.cpp
        src/system.cpp
        
        src/polymorphic/polymanager.cpp
    )

    target_include_directories(${TARGET_NAME} PUBLIC
        ${CORE_SOURCE_DIR}/include
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