set(CORE_STATIC ON CACHE BOOL "Build the core library as a static library" PARENT_SCOPE)
set(CORE_SHARED OFF CACHE BOOL "Build the core library as a shared library" PARENT_SCOPE)
set(CORE_BUILD_EXAMPLES OFF CACHE BOOL "Build executables in the examples directory")

message("-------------------------------")
message("-- C++ Codebase Core Options --")
message("--")
set(OPTIONS "CORE_STATIC" "CORE_SHARED" "CORE_BUILD_EXAMPLES")
foreach(item ${OPTIONS})
    message(STATUS "${item}: ${${item}}")
endforeach()

message("-------------------------------")