#include "logic.h"
#include "unity.h"

#include <stddef.h>

Operator ops[] = { { .name = "AND" } };
size_t ops_len = 1;

void setUp(void) {}
void tearDown(void) {}

void test_str_to_operator_idx_if_null_name(void)
{
	TEST_ASSERT_EQUAL_INT(-1, str_to_operator_idx(NULL, ops, ops_len));
}

void test_str_to_operator_idx_if_not_operator(void)
{
	TEST_ASSERT_EQUAL_INT(-2, str_to_operator_idx("foo", ops, ops_len));	
}

void test_str_to_operator_idx_if_valid_operator(void)
{
	TEST_ASSERT_EQUAL_INT(0, str_to_operator_idx("AND", ops, ops_len));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_str_to_operator_idx_if_null_name);
	RUN_TEST(test_str_to_operator_idx_if_not_operator);
	RUN_TEST(test_str_to_operator_idx_if_valid_operator);
	return UNITY_END();
}
