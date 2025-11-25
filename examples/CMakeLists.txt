add_executable(cpp-codebase-example1
    example1.cpp
)
target_include_directories(cpp-codebase-example1 PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_link_libraries(cpp-codebase-example1 PUBLIC core)