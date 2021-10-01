#include "logic.h"
#include "unity.h"

#include <stdlib.h>

Queue *ex;

Variable vars[] =
{
	{ .name = "foo", .value = 0 },
	{ .name = "bar", .value = 1 }
};
size_t vars_len = 2;

void setUp(void)
{
	ex = Queue_new();
}

void tearDown(void)
{
	Queue_free(ex);
}

void test_evaluate_expression_should_return_null_if_exp_is_null(void)
{
	TEST_ASSERT_NULL(evaluate_expression(NULL, vars, vars_len));
}

void test_evaluate_expression_should_return_empty_list_if_exp_is_empty(void)
{
	Queue *ret = evaluate_expression(ex, vars, vars_len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_NULL(ret->front);
	TEST_ASSERT_NULL(ret->back);
	free(ret);
}

void test_evaluate_expression_should_handle_single_operator(void)
{
	Queue_push(ex, "NOT");
	Queue *ret = evaluate_expression(ex, vars, vars_len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_NOT_NULL(ret->front);
	TEST_ASSERT_NOT_NULL(ret->back);
	TEST_ASSERT_EQUAL_PTR(ret->front, ret->back);
	TEST_ASSERT_EQUAL_STRING("NOT", ret->back->data);
	free(ret);
}

void test_evaluate_expression_should_handle_single_variable(void)
{
	Queue_push(ex, "foo");
	Queue *ret = evaluate_expression(ex, vars, vars_len);
	TEST_ASSERT_NOT_NULL(ret);
	TEST_ASSERT_NOT_NULL(ret->front);
	TEST_ASSERT_NOT_NULL(ret->back);
	TEST_ASSERT_EQUAL_PTR(ret->front, ret->back);
	TEST_ASSERT_EQUAL_STRING("0", ret->back->data);
	free(ret);
}

void test_evaluate_expression_should_handle_complex_expression(void)
{
	Queue_push(ex, "foo");
	Queue_push(ex, "bar");
	Queue_push(ex, "AND");
	Queue_push(ex, "foo");
	Queue_push(ex, "XOR");

	Queue *ret = evaluate_expression(ex, vars, vars_len);

	QNode *node = ret->front;
	TEST_ASSERT_EQUAL_STRING("0", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("1", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("0", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("XOR", node->data);
	node = node->next;

	free(ret);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_evaluate_expression_should_return_null_if_exp_is_null);
	RUN_TEST(test_evaluate_expression_should_return_empty_list_if_exp_is_empty);
	RUN_TEST(test_evaluate_expression_should_handle_single_operator);
	RUN_TEST(test_evaluate_expression_should_handle_single_variable);
	RUN_TEST(test_evaluate_expression_should_handle_complex_expression);
	return UNITY_END();
}
