#include "logic.h"
#include "unity.h"

List *ex;

Operator ops[] =
{
	{ .name = "NOT", .precedence = 1, .arity = 1, .associativity = RIGHT_ASSOC, .function.unary = logical_not },
	{ .name = "AND", .precedence = 2, .arity = 2, .associativity = LEFT_ASSOC, .function.binary = logical_and },
	{ .name = "OR", .precedence = 3, .arity = 2, .associativity = LEFT_ASSOC, .function.binary = logical_or },
	{ .name = "XOR", .precedence = 4, .arity = 2, .associativity = LEFT_ASSOC, .function.binary = logical_xor },
	{ .name = "IMPLY", .precedence = 5, .arity = 2, .associativity = RIGHT_ASSOC, .function.binary = logical_imply }
};
size_t ops_len = 5;

void setUp(void)
{
	ex = List_new();
}

void tearDown(void)
{
	List_free(ex);
}

void test_calculate_should_return_true_if_exp_is_null(void)
{
	TEST_ASSERT_EQUAL(1, calculate(ex, ops, ops_len));
}

void test_calculate_should_return_true_if_exp_is_empty(void)
{
	TEST_ASSERT_EQUAL(1, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_single_value(void)
{
	List_push_back(ex, "0");
	TEST_ASSERT_EQUAL(0, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_unary_operator(void)
{
	List_push_back(ex, "0");
	List_push_back(ex, "NOT");
	TEST_ASSERT_EQUAL(1, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_binary_operator(void)
{
	List_push_back(ex, "0");
	List_push_back(ex, "1");
	List_push_back(ex, "AND");
	TEST_ASSERT_EQUAL(0, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_multiple_operators(void)
{
	List_push_back(ex, "0");
	List_push_back(ex, "NOT");
	List_push_back(ex, "1");
	List_push_back(ex, "AND");
	List_push_back(ex, "0");
	List_push_back(ex, "XOR");
	List_push_back(ex, "0");
	List_push_back(ex, "IMPLY");
	TEST_ASSERT_EQUAL(0, calculate(ex, ops, ops_len));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_calculate_should_return_true_if_exp_is_null);
	RUN_TEST(test_calculate_should_return_true_if_exp_is_empty);
	RUN_TEST(test_calculate_should_handle_single_value);
	RUN_TEST(test_calculate_should_handle_unary_operator);
	RUN_TEST(test_calculate_should_handle_binary_operator);
	RUN_TEST(test_calculate_should_handle_multiple_operators);
	return UNITY_END();
}
