cmake_minimum_required(VERSION 3.0)
project(bfaas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror" )

add_subdirectory(bflib)
add_subdirectory(bfapp)
