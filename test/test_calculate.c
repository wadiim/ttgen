#include "logic.h"
#include "unity.h"

Queue *ex;

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
	ex = Queue_new();
}

void tearDown(void)
{
	Queue_free(ex);
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
	Queue_push(ex, "0");
	TEST_ASSERT_EQUAL(0, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_unary_operator(void)
{
	Queue_push(ex, "0");
	Queue_push(ex, "NOT");
	TEST_ASSERT_EQUAL(1, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_binary_operator(void)
{
	Queue_push(ex, "0");
	Queue_push(ex, "1");
	Queue_push(ex, "AND");
	TEST_ASSERT_EQUAL(0, calculate(ex, ops, ops_len));
}

void test_calculate_should_handle_multiple_operators(void)
{
	Queue_push(ex, "0");
	Queue_push(ex, "NOT");
	Queue_push(ex, "1");
	Queue_push(ex, "AND");
	Queue_push(ex, "0");
	Queue_push(ex, "XOR");
	Queue_push(ex, "0");
	Queue_push(ex, "IMPLY");
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
