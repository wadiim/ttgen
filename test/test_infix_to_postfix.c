#include "logic.h"
#include "unity.h"

#include <stddef.h>

List *ex;
Queue *postfix;
Operator ops[] =
{
	{ .name = "NOT", .precedence = 1, .arity = 1, .associativity = RIGHT_ASSOC },
	{ .name = "AND", .precedence = 2, .arity = 2, .associativity = LEFT_ASSOC },
	{ .name = "OR", .precedence = 3, .arity = 2, .associativity = LEFT_ASSOC },
	{ .name = "XOR", .precedence = 4, .arity = 2, .associativity = LEFT_ASSOC },
	{ .name = "IMPLY", .precedence = 5, .arity = 2, .associativity = RIGHT_ASSOC }
};
size_t ops_len = 5;

void setUp(void)
{
	ex = List_new();
}

void tearDown(void)
{
	List_free(ex);
	Queue_free(postfix);
}

void test_infix_to_postfix_should_set_postfix_to_null_if_exp_is_null(void)
{
	infix_to_postfix(NULL, ops, ops_len, &postfix);
	TEST_ASSERT_NULL(postfix);
	postfix = Queue_new(); // Avoids passing NULL to Queue_free().
}

void test_infix_to_postfix_should_make_postfix_empty_if_exp_is_empty(void)
{
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_NOT_NULL(postfix);
	TEST_ASSERT_NULL(postfix->front);
	TEST_ASSERT_NULL(postfix->back);
}

void test_infix_to_postfix_should_make_postfix_empty_if_only_parentheses(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, ")");
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_NOT_NULL(postfix);
	TEST_ASSERT_NULL(postfix->front);
	TEST_ASSERT_NULL(postfix->back);
}

void test_infix_to_postfix_should_handle_single_variable(void)
{
	List_push_back(ex, "foo");
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_EQUAL_PTR(postfix->front, postfix->back);
	TEST_ASSERT_EQUAL_STRING("foo", postfix->front->data);
}

void test_infix_to_postfix_should_handle_single_operator(void)
{
	List_push_back(ex, "NOT");
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_EQUAL_PTR(postfix->front, postfix->back);
	TEST_ASSERT_EQUAL_STRING("NOT", postfix->front->data);
}

void test_infix_to_postfix_should_exclude_parentheses_from_postfix(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, ")");
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_EQUAL_PTR(postfix->front, postfix->back);
	TEST_ASSERT_EQUAL_STRING("foo", postfix->front->data);
}

void test_infix_to_postfix_should_handle_operator_with_arity_eq_1(void)
{
	List_push_back(ex, "NOT");
	List_push_back(ex, "foo");
	infix_to_postfix(ex, ops, ops_len, &postfix);
	TEST_ASSERT_EQUAL_STRING("foo", postfix->front->data);
	TEST_ASSERT_EQUAL_STRING("NOT", postfix->back->data);
}

void test_infix_to_postfix_should_handle_operator_with_arity_eq_2(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	List_push_back(ex, "AND");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
}

void test_infix_to_postfix_should_handle_operators_with_left_associativity(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	List_push_back(ex, "AND");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
}

void test_infix_to_postfix_should_handle_operators_with_right_associativity(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "IMPLY");
	List_push_back(ex, "bar");
	List_push_back(ex, "IMPLY");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("IMPLY", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("IMPLY", node->data);
}

void test_infix_to_postfix_should_handle_operators_with_different_precedences(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "OR");
	List_push_back(ex, "bar");
	List_push_back(ex, "AND");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("OR", node->data);
}

void test_infix_to_postfix_should_handle_operators_with_different_associativities(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	List_push_back(ex, "IMPLY");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("IMPLY", node->data);
}

void test_infix_to_postfix_should_handle_parentheses(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "OR");
	List_push_back(ex, "bar");
	List_push_back(ex, ")");
	List_push_back(ex, "AND");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("OR", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("AND", node->data);
	node = node->next;
}

void test_infix_to_postfix_should_return_non_zero_value_if_too_few_opening_parentheses(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "OR");
	List_push_back(ex, "bar");
	List_push_back(ex, "XOR");
	List_push_back(ex, "baz");
	List_push_back(ex, ")");
	List_push_back(ex, ")");

	TEST_ASSERT_NOT_EQUAL_INT(0, infix_to_postfix(ex, ops, ops_len, &postfix));
}

void test_infix_to_postfix_should_return_non_zero_value_if_too_few_closing_parentheses(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "OR");
	List_push_back(ex, "bar");
	List_push_back(ex, ")");
	List_push_back(ex, "XOR");
	List_push_back(ex, "baz");

	TEST_ASSERT_NOT_EQUAL_INT(0, infix_to_postfix(ex, ops, ops_len, &postfix));
}

void test_infix_to_postfix_should_handle_lowercase_operators(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "or");
	List_push_back(ex, "bar");
	List_push_back(ex, ")");
	List_push_back(ex, "and");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("or", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("and", node->data);
	node = node->next;
}

void test_infix_to_postfix_should_handle_mixedcase_operators(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "Or");
	List_push_back(ex, "bar");
	List_push_back(ex, ")");
	List_push_back(ex, "aND");
	List_push_back(ex, "baz");

	infix_to_postfix(ex, ops, ops_len, &postfix);

	QNode *node = postfix->front;
	TEST_ASSERT_EQUAL_STRING("foo", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("bar", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("Or", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("baz", node->data);
	node = node->next;
	TEST_ASSERT_EQUAL_STRING("aND", node->data);
	node = node->next;
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_infix_to_postfix_should_set_postfix_to_null_if_exp_is_null);
	RUN_TEST(test_infix_to_postfix_should_make_postfix_empty_if_exp_is_empty);
	RUN_TEST(test_infix_to_postfix_should_make_postfix_empty_if_only_parentheses);
	RUN_TEST(test_infix_to_postfix_should_handle_single_variable);
	RUN_TEST(test_infix_to_postfix_should_handle_single_operator);
	RUN_TEST(test_infix_to_postfix_should_exclude_parentheses_from_postfix);
	RUN_TEST(test_infix_to_postfix_should_handle_operator_with_arity_eq_1);
	RUN_TEST(test_infix_to_postfix_should_handle_operator_with_arity_eq_2);
	RUN_TEST(test_infix_to_postfix_should_handle_operators_with_left_associativity);
	RUN_TEST(test_infix_to_postfix_should_handle_operators_with_right_associativity);
	RUN_TEST(test_infix_to_postfix_should_handle_operators_with_different_precedences);
	RUN_TEST(test_infix_to_postfix_should_handle_operators_with_different_associativities);
	RUN_TEST(test_infix_to_postfix_should_handle_parentheses);
	RUN_TEST(test_infix_to_postfix_should_return_non_zero_value_if_too_few_opening_parentheses);
	RUN_TEST(test_infix_to_postfix_should_return_non_zero_value_if_too_few_closing_parentheses);
	RUN_TEST(test_infix_to_postfix_should_handle_lowercase_operators);
	RUN_TEST(test_infix_to_postfix_should_handle_mixedcase_operators);
	return UNITY_END();
}
