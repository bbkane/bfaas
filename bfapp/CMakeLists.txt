project(bfapp)

add_executable(bfapp main.c)

target_link_libraries(bfapp LINK_PUBLIC bf)

