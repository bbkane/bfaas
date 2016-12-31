cmake_minimum_required(VERSION 3.0)
project(bf)

set(BF_LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/bf.c" "${CMAKE_CURRENT_SOURCE_DIR}/bf.h")

add_library(bf "${BF_LIB_FILES}")

add_custom_target(makeheaders
    COMMAND makeheaders ${BF_LIB_FILES})
add_dependencies(bf makeheaders)


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello
target_include_directories (bf PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
