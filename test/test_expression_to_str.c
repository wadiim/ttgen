#include "logic.h"
#include "unity.h"

#include <stdlib.h>

List *ex;

void setUp(void)
{
	ex = List_new();
}

void tearDown(void)
{
	List_free(ex);
}

void test_expression_to_str_should_return_null_if_exp_is_null(void)
{
	TEST_ASSERT_NULL(expression_to_str(NULL));
}

void test_expression_to_str_should_return_empty_string_if_exp_is_empty(void)
{
	char *ret = expression_to_str(ex);
	TEST_ASSERT_EQUAL_STRING("", ret);
	free(ret);
}

void test_expression_to_str_should_handle_single_token(void)
{
	List_push_back(ex, "foo");
	char *ret = expression_to_str(ex);
	TEST_ASSERT_EQUAL_STRING("foo", ret);
	free(ret);
}

void test_expression_to_str_should_handle_multiple_tokens(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, "AND");
	List_push_back(ex, "bar");
	char *ret = expression_to_str(ex);
	TEST_ASSERT_EQUAL_STRING("foo AND bar", ret);
	free(ret);
}

void test_expression_to_str_should_handle_expression_with_parentheses(void)
{
	List_push_back(ex, "(");
	List_push_back(ex, "(");
	List_push_back(ex, "foo");
	List_push_back(ex, "OR");
	List_push_back(ex, "bar");
	List_push_back(ex, ")");
	List_push_back(ex, "AND");
	List_push_back(ex, "(");
	List_push_back(ex, "baz");
	List_push_back(ex, ")");
	List_push_back(ex, ")");

	char *ret = expression_to_str(ex);
	TEST_ASSERT_EQUAL_STRING("((foo OR bar) AND (baz))", ret);
	free(ret);
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_expression_to_str_should_return_null_if_exp_is_null);
	RUN_TEST(test_expression_to_str_should_return_empty_string_if_exp_is_empty);
	RUN_TEST(test_expression_to_str_should_handle_single_token);
	RUN_TEST(test_expression_to_str_should_handle_multiple_tokens);
	RUN_TEST(test_expression_to_str_should_handle_expression_with_parentheses);
	return UNITY_END();
}
