cmake_minimum_required(VERSION 3.0)
project(bfaas)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror" )

set(BF_LIB_FILES "${CMAKE_SOURCE_DIR}/bf.c" "${CMAKE_SOURCE_DIR}/bf.h")

add_custom_target(makeheaders
    COMMAND makeheaders ${BF_LIB_FILES})

add_executable(bfaas "${BF_LIB_FILES}" main.c)
add_dependencies(bfaas makeheaders)
