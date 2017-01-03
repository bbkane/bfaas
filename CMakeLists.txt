cmake_minimum_required(VERSION 3.0)
project(bfaas)

# Add compile options for all subsequent projects
if (MSVC)
    add_compile_options(/W4)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-std=c11 -Weverything -g -O0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" -O0)
    add_compile_options(-std=c11 -Weverything -g -O0)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-std=c11 -Wall -Wextra -pedantic -g -O0)
endif(MSVC)

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

add_subdirectory(bf)
add_subdirectory(bfapp)
add_subdirectory(bftest)
