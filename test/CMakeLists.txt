add_library(unity STATIC unity/unity.c)
target_include_directories(unity PUBLIC unity)

add_executable(test_evaluate_expression test_evaluate_expression.c)
target_link_libraries(test_evaluate_expression logic unity)

add_executable(test_expression_to_str test_expression_to_str.c)
target_link_libraries(test_expression_to_str logic unity)

add_executable(test_get_variables test_get_variables.c)
target_link_libraries(test_get_variables logic unity)

add_executable(test_infix_to_postfix test_infix_to_postfix.c)
target_link_libraries(test_infix_to_postfix logic unity)

add_executable(test_list test_list.c)
target_link_libraries(test_list list unity)

add_executable(test_queue test_queue.c)
target_link_libraries(test_queue queue unity)

add_executable(test_stack test_stack.c)
target_link_libraries(test_stack stack unity)

add_executable(test_str_to_operator_idx test_str_to_operator_idx.c)
target_link_libraries(test_str_to_operator_idx logic unity)

add_executable(test_str_to_variable_idx test_str_to_variable_idx.c)
target_link_libraries(test_str_to_variable_idx logic unity)

add_executable(test_split_expression test_split_expression.c)
target_link_libraries(test_split_expression logic unity)

add_executable(test_tokenize test_tokenize.c)
target_link_libraries(test_tokenize logic unity)

add_executable(test_update_variables test_update_variables.c)
target_link_libraries(test_update_variables logic unity)

add_executable(test_utils test_utils.c)
target_link_libraries(test_utils utils unity)
