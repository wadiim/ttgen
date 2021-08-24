add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC unity)

add_executable(test_get_variables test_get_variables.c)
target_link_libraries(test_get_variables logic list utils unity)

add_executable(test_list test_list.c)
target_link_libraries(test_list list unity)

add_executable(test_split_expression test_split_expression.c)
target_link_libraries(test_split_expression logic list utils unity)

add_executable(test_tokenize test_tokenize.c)
target_link_libraries(test_tokenize logic list utils unity)

add_executable(test_update_variables test_update_variables.c)
target_link_libraries(test_update_variables logic list utils unity)

add_executable(test_utils test_utils.c)
target_link_libraries(test_utils utils unity)
