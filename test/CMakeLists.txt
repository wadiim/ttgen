add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC unity)

add_executable(test_list test_list.c)
add_executable(test_logic test_logic.c)

target_link_libraries(test_list list unity)
target_link_libraries(test_logic logic list unity)
