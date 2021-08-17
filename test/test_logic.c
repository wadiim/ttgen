#include "list.h"
#include "logic.h"
#include "unity.h"

#include <string.h>

List *list;

void setUp(void)
{
	list = List_new();
}

void tearDown(void)
{
	List_free(list);
}

void test_tokenize_should_return_empty_list_if_str_is_empty(void)
{
	list = tokenize("");
	TEST_ASSERT_EQUAL(0, List_length(list));
}

void test_tokenize_should_handle_single_word(void)
{
	list = tokenize("foo1337");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("foo1337", list->back->data);
}

void test_tokenize_should_handle_single_integer(void)
{
	list = tokenize("22");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("22", list->back->data);
}

void test_tokenize_should_handle_single_left_parenthesis(void)
{
	list = tokenize("(");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("(", list->back->data);
}

void test_tokenize_should_handle_single_right_parenthesis(void)
{
	list = tokenize(")");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING(")", list->back->data);
}

void test_tokenize_should_remove_whitespaces_if_single_word(void)
{
	list = tokenize(" \t  foo\n  \r\v");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("foo", list->back->data);
}

void test_tokenize_should_remove_whitespaces_if_single_integer(void)
{
	list = tokenize("\t \r22 \v\n");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("22", list->back->data);
}

void test_tokenize_should_remove_whitespaces_if_single_left_parenthesis(void)
{
	list = tokenize("\v \r ( \n");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING("(", list->back->data);
}

void test_tokenize_should_remove_whitespaces_if_single_right_parenthesis(void)
{
	list = tokenize("\r )\t \n\v");
	TEST_ASSERT_EQUAL(1, List_length(list));
	TEST_ASSERT_EQUAL_STRING(")", list->back->data);
}

void test_tokenize_should_handle_multiple_words(void)
{
	list = tokenize("foo bar baz");
	TEST_ASSERT_EQUAL(3, List_length(list));
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->front->next->data);
	TEST_ASSERT_EQUAL_STRING("baz", list->back->data);
}

void test_tokenize_should_handle_multiple_integers(void)
{
	list = tokenize("2 1337 22");
	TEST_ASSERT_EQUAL(3, List_length(list));
	TEST_ASSERT_EQUAL_STRING("2", list->front->data);
	TEST_ASSERT_EQUAL_STRING("1337", list->front->next->data);
	TEST_ASSERT_EQUAL_STRING("22", list->back->data);
}

void test_tokenize_should_handle_integer_immediately_followed_by_word(void)
{
	list = tokenize("1337foo");
	TEST_ASSERT_EQUAL(2, List_length(list));
	TEST_ASSERT_EQUAL_STRING("1337", list->front->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->back->data);
}

void test_tokenize_should_treat_each_parenthesis_as_separate_token(void)
{
	const char *str = "()(()(";
	size_t str_len = strlen(str);
	list = tokenize(str);
	TEST_ASSERT_EQUAL(str_len, List_length(list));

	Node *node = list->front;
	for (size_t i = 0; i < str_len && node; ++i)
	{
		TEST_ASSERT_EQUAL(1, strlen(node->data));
		TEST_ASSERT_EQUAL_CHAR(str[i], node->data[0]);
		node = node->next;
	}
}

void test_tokenize_should_handle_word_surrounded_by_parentheses(void)
{
	list = tokenize("(foo)");
	TEST_ASSERT_EQUAL(3, List_length(list));
	TEST_ASSERT_EQUAL_STRING("(", list->front->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->next->data);
	TEST_ASSERT_EQUAL_STRING(")", list->back->data);
}

void test_tokenize_should_return_empty_list_if_str_contains_only_whitespaces(void)
{
	list = tokenize("  \t  \r      \v    \n \n \r  ");
	TEST_ASSERT_EQUAL(0, List_length(list));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_tokenize_should_return_empty_list_if_str_is_empty);
	RUN_TEST(test_tokenize_should_handle_single_word);
	RUN_TEST(test_tokenize_should_handle_single_integer);
	RUN_TEST(test_tokenize_should_handle_single_left_parenthesis);
	RUN_TEST(test_tokenize_should_handle_single_right_parenthesis);
	RUN_TEST(test_tokenize_should_remove_whitespaces_if_single_word);
	RUN_TEST(test_tokenize_should_remove_whitespaces_if_single_integer);
	RUN_TEST(test_tokenize_should_remove_whitespaces_if_single_left_parenthesis);
	RUN_TEST(test_tokenize_should_remove_whitespaces_if_single_right_parenthesis);
	RUN_TEST(test_tokenize_should_handle_multiple_words);
	RUN_TEST(test_tokenize_should_handle_multiple_integers);
	RUN_TEST(test_tokenize_should_handle_integer_immediately_followed_by_word);
	RUN_TEST(test_tokenize_should_treat_each_parenthesis_as_separate_token);
	RUN_TEST(test_tokenize_should_handle_word_surrounded_by_parentheses);
	RUN_TEST(test_tokenize_should_return_empty_list_if_str_contains_only_whitespaces);
	return UNITY_END();
}
