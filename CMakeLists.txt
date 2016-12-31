cmake_minimum_required(VERSION 3.0)
project(bfaas)

# Add compile options for all subsequent projects
if (MSVC)
    add_compile_options(/W4)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
    add_compile_options(-std=c11 -Weverything -g)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(-std=c11 -Weverything -g)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-std=c11 -Wall -Wextra -pedantic -g)
endif(MSVC)

add_subdirectory(bf)
add_subdirectory(bfapp)
add_subdirectory(bftest)
