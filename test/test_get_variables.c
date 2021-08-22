#include "list.h"
#include "logic.h"
#include "unity.h"

#include <stddef.h>
#include <stdlib.h>

List *ex;

Operator ops[] =
{
	{"NOT"},
	{"AND"},
	{"OR"}
};
size_t ops_len = sizeof(ops)/sizeof(ops[0]);

Variable *vars;
size_t vars_len;

void setUp(void)
{
	ex = List_new();
}

void tearDown(void)
{
	free(vars);
	List_free(ex);
}

void test_get_variables_should_set_vars_len_to_0_if_exp_is_empty(void)
{
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	TEST_ASSERT_EQUAL(0, vars_len);
}

void test_get_variables_should_set_vars_len_to_0_if_exp_has_no_variables(void)
{
	List_push_back(ex, "NOT");
	List_push_back(ex, "AND");
	List_push_back(ex, "OR");
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	TEST_ASSERT_EQUAL(0, vars_len);
}

void test_get_variables_should_set_vars_len_to_number_of_vars_in_exp(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "bar");
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	TEST_ASSERT_EQUAL(2, vars_len);
}

void test_get_variables_should_set_vars_len_correctly_if_exp_has_both_ops_and_vars(void)
{
	List_push_back(ex, "NOT");
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	TEST_ASSERT_EQUAL(2, vars_len);
}

void test_get_variables_should_store_variables_from_exp_in_vars_array(void)
{
	List_push_back(ex, "NOT");
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	TEST_ASSERT_EQUAL_STRING("foo", vars[0].name);
	TEST_ASSERT_EQUAL_STRING("bar", vars[1].name);
}

void test_get_variables_should_do_shallow_copy_of_var_names(void)
{
	List_push_back(ex, "foo");
	get_variables(ex, ops, ops_len, &vars, &vars_len);
	ex->front->data[0] = 'b';
	TEST_ASSERT_EQUAL_STRING("boo", vars[0].name);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_get_variables_should_set_vars_len_to_0_if_exp_is_empty);
	RUN_TEST(test_get_variables_should_set_vars_len_to_0_if_exp_has_no_variables);
	RUN_TEST(test_get_variables_should_set_vars_len_to_number_of_vars_in_exp);
	RUN_TEST(test_get_variables_should_set_vars_len_correctly_if_exp_has_both_ops_and_vars);
	RUN_TEST(test_get_variables_should_store_variables_from_exp_in_vars_array);
	RUN_TEST(test_get_variables_should_do_shallow_copy_of_var_names);
	return UNITY_END();
}
