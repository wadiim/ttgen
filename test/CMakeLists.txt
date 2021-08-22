add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC unity)

add_executable(test_list test_list.c)
add_executable(test_tokenize test_tokenize.c)
add_executable(test_utils test_utils.c)

target_link_libraries(test_list list unity)
target_link_libraries(test_tokenize logic list utils unity)
target_link_libraries(test_utils utils unity)
