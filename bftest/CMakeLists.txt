project(bftest)

add_executable(bftest main.c)

target_link_libraries(bftest LINK_PUBLIC bf)

add_custom_target(valgrind 
    COMMAND valgrind --tool=memcheck --leak-check=yes --show-reachable=yes --num-callers=20 --track-fds=yes $<TARGET_FILE:bftest>)
