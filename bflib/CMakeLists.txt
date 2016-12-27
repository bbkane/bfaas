cmake_minimum_required(VERSION 3.0)
project(bflib)

set(BF_LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/bf.c" "${CMAKE_CURRENT_SOURCE_DIR}/bf.h")

add_library(bflib "${BF_LIB_FILES}")
add_custom_target(makeheaders
    COMMAND makeheaders ${BF_LIB_FILES})
add_dependencies(bflib makeheaders)

# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (bflib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
