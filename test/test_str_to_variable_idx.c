#include "logic.h"
#include "unity.h"

#include <stddef.h>

Variable vars[] = { { .name = "foo" } };
size_t vars_len = 1;

void setUp(void) {}
void tearDown(void) {}

void test_str_to_variable_idx_if_null_name(void)
{
	TEST_ASSERT_EQUAL_INT(-1, str_to_variable_idx(NULL, vars, vars_len));
}

void test_str_to_variable_idx_if_not_variable(void)
{
	TEST_ASSERT_EQUAL_INT(-2, str_to_variable_idx("?", vars, vars_len));	
}

void test_str_to_variable_idx_if_valid_variable(void)
{
	TEST_ASSERT_EQUAL_INT(0, str_to_variable_idx("foo", vars, vars_len));
}

void test_str_to_variable_idx_if_uppercase_variable(void)
{
	TEST_ASSERT_EQUAL_INT(-2, str_to_variable_idx("FOO", vars, vars_len));
}

void test_str_to_variable_idx_if_mixedcase_variable(void)
{
	TEST_ASSERT_EQUAL_INT(-2, str_to_variable_idx("FoO", vars, vars_len));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_str_to_variable_idx_if_null_name);
	RUN_TEST(test_str_to_variable_idx_if_not_variable);
	RUN_TEST(test_str_to_variable_idx_if_valid_variable);
	RUN_TEST(test_str_to_variable_idx_if_uppercase_variable);
	RUN_TEST(test_str_to_variable_idx_if_mixedcase_variable);
	return UNITY_END();
}
