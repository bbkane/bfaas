cmake_minimum_required(VERSION 3.0)
project(bfaas)

add_compile_options(-Wall -Werror -pedantic -g)

add_subdirectory(bf)
add_subdirectory(bfapp)
add_subdirectory(bftest)
