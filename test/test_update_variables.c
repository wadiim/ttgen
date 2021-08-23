#include "logic.h"
#include "unity.h"

#include <stddef.h>
#include <stdlib.h>

Variable vars[3];
size_t vars_len = 3;

void setUp(void)
{
	vars[0].name = "foo";
	vars[1].name = "bar";
	vars[2].name = "baz";
	for (size_t i = 0; i < vars_len; ++i) vars[i].value = 0;
}

void tearDown(void) {}

void test_update_variables_should_return_false_if_vars_len_is_0(void)
{
	TEST_ASSERT_FALSE(update_variables(NULL, 0));
}

void test_update_variables_should_return_false_if_all_values_are_1(void)
{
	for (size_t i = 0; i < vars_len; ++i) vars[i].value = 1;
	TEST_ASSERT_FALSE(update_variables(vars, vars_len));
}

void test_update_variables_should_not_modify_values_if_all_are_1(void)
{
	for (size_t i = 0; i < vars_len; ++i) vars[i].value = 1;
	update_variables(vars, vars_len);
	for (size_t i = 0; i < vars_len; ++i)
	{
		TEST_ASSERT_EQUAL(1, vars[i].value);
	}
}

void test_update_variables_should_return_true_if_not_all_values_are_1(void)
{
	TEST_ASSERT_TRUE(update_variables(vars, vars_len));
	vars[0].value = 1;
	vars[1].value = 0;
	vars[2].value = 0;
	TEST_ASSERT_TRUE(update_variables(vars, vars_len));
	vars[0].value = 1;
	vars[1].value = 0;
	vars[2].value = 1;
	TEST_ASSERT_TRUE(update_variables(vars, vars_len));
}

void test_update_variables_should_set_the_last_value_to_1_if_it_is_0(void)
{
	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(1, vars[vars_len-1].value);
}

void test_update_variables_should_treat_values_as_digits_of_binary_num_and_increment_it(void)
{
	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(0, vars[0].value);
	TEST_ASSERT_EQUAL(0, vars[1].value);
	TEST_ASSERT_EQUAL(1, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(0, vars[0].value);
	TEST_ASSERT_EQUAL(1, vars[1].value);
	TEST_ASSERT_EQUAL(0, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(0, vars[0].value);
	TEST_ASSERT_EQUAL(1, vars[1].value);
	TEST_ASSERT_EQUAL(1, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(1, vars[0].value);
	TEST_ASSERT_EQUAL(0, vars[1].value);
	TEST_ASSERT_EQUAL(0, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(1, vars[0].value);
	TEST_ASSERT_EQUAL(0, vars[1].value);
	TEST_ASSERT_EQUAL(1, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(1, vars[0].value);
	TEST_ASSERT_EQUAL(1, vars[1].value);
	TEST_ASSERT_EQUAL(0, vars[2].value);

	update_variables(vars, vars_len);
	TEST_ASSERT_EQUAL(1, vars[0].value);
	TEST_ASSERT_EQUAL(1, vars[1].value);
	TEST_ASSERT_EQUAL(1, vars[2].value);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_update_variables_should_return_false_if_vars_len_is_0);
	RUN_TEST(test_update_variables_should_return_false_if_all_values_are_1);
	RUN_TEST(test_update_variables_should_not_modify_values_if_all_are_1);
	RUN_TEST(test_update_variables_should_return_true_if_not_all_values_are_1);
	RUN_TEST(test_update_variables_should_set_the_last_value_to_1_if_it_is_0);
	RUN_TEST(test_update_variables_should_treat_values_as_digits_of_binary_num_and_increment_it);
	return UNITY_END();
}
