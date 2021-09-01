#include "list.h"
#include "logic.h"
#include "unity.h"

#include <stdlib.h>

List *ex;
List *exps;
size_t exps_size;

void setUp(void)
{
	ex = List_new();
}

void tearDown(void)
{
	free(exps);
}

/*
 * Checks if the 'exps' array consist of a single expression with a
 * single token and if its name is 'name'.
 */
static void check_if_exps_contains_single_list_with_single_node(const char *name)
{
	TEST_ASSERT_EQUAL(1, exps_size);
	TEST_ASSERT_NOT_NULL(exps[0].front);
	TEST_ASSERT_NOT_NULL(exps[0].back);
	TEST_ASSERT_EQUAL_PTR(exps[0].front, exps[0].back);
	TEST_ASSERT_NOT_NULL(exps[0].back->data);
	TEST_ASSERT_EQUAL_STRING(name, exps[0].back->data);
}

void test_split_expression_should_return_0_if_exp_is_empty(void)
{
	TEST_ASSERT_EQUAL_INT(0, split_expression(ex, &exps, &exps_size));
}

void test_split_expression_should_initialize_exps_to_single_empty_list_if_exp_is_empty(void)
{
	split_expression(ex, &exps, &exps_size);
	TEST_ASSERT_EQUAL(1, exps_size);
	TEST_ASSERT_NULL(exps[0].front);
	TEST_ASSERT_NULL(exps[0].back);
}

void test_split_expression_should_initialize_exps_to_exp_if_no_separator_presented(void)
{
	List_push_back(ex, "foo");
	split_expression(ex, &exps, &exps_size);
	check_if_exps_contains_single_list_with_single_node("foo");
}

void test_split_expression_should_do_shallow_copy_of_list_nodes(void)
{
	List_push_back(ex, "foo");
	split_expression(ex, &exps, &exps_size);
	ex->back->data[0] = 'b';
	TEST_ASSERT_EQUAL_STRING("boo", exps[0].back->data);
}

void test_split_expression_if_separators_are_presented(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, ";");
	List_push_back(ex, "NOT");
	List_push_back(ex, "bar");
	List_push_back(ex, ";");
	List_push_back(ex, "qux");
	List_push_back(ex, "XOR");
	List_push_back(ex, "qux");

	split_expression(ex, &exps, &exps_size);
	TEST_ASSERT_EQUAL(3, exps_size);
	for (size_t i = 0; i < exps_size; ++i)
	{
		TEST_ASSERT_NOT_NULL(exps[i].front);
		TEST_ASSERT_NOT_NULL(exps[i].back);
		TEST_ASSERT_NULL(exps[i].front->prev);
		TEST_ASSERT_NULL(exps[i].back->next);

		for (LNode *n = exps[i].front; n != NULL; n = n->next)
		{
			TEST_ASSERT_NOT_NULL(n->data);
			if (n != exps[i].back)
			{
				TEST_ASSERT_EQUAL_STRING(n->data,
						n->next->prev->data);
			}
			if (n != exps[i].front)
			{
				TEST_ASSERT_EQUAL_STRING(n->data,
						n->prev->next->data);
			}
		}
	}

	TEST_ASSERT_EQUAL_STRING("foo", exps[0].front->data);

	TEST_ASSERT_EQUAL_STRING("NOT", exps[1].front->data);
	TEST_ASSERT_EQUAL_STRING("bar", exps[1].back->data);

	TEST_ASSERT_EQUAL_STRING("qux", exps[2].front->data);
	TEST_ASSERT_EQUAL_STRING("XOR", exps[2].front->next->data);
	TEST_ASSERT_EQUAL_STRING("qux", exps[2].back->data);
}

void test_split_expression_should_handle_trailing_separator(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, ";");
	split_expression(ex, &exps, &exps_size);
	check_if_exps_contains_single_list_with_single_node("foo");
}

void test_split_expression_should_handle_precending_separator(void)
{
	List_push_back(ex, ";");
	List_push_back(ex, "foo");
	split_expression(ex, &exps, &exps_size);
	check_if_exps_contains_single_list_with_single_node("foo");
}

void test_split_expression_should_handle_inner_adjacent_separators(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	List_push_back(ex, "bar");
	split_expression(ex, &exps, &exps_size);
	TEST_ASSERT_EQUAL(2, exps_size);
	TEST_ASSERT_EQUAL_STRING("foo", exps[0].front->data);
	TEST_ASSERT_EQUAL_STRING("bar", exps[1].front->data);
}

void test_split_expression_should_handle_trailing_adjacent_separators(void)
{
	List_push_back(ex, "foo");
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	split_expression(ex, &exps, &exps_size);
	check_if_exps_contains_single_list_with_single_node("foo");
}

void test_split_expression_should_handle_precending_adjacent_separators(void)
{
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	List_push_back(ex, ";");
	List_push_back(ex, "foo");
	split_expression(ex, &exps, &exps_size);
	check_if_exps_contains_single_list_with_single_node("foo");
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_split_expression_should_return_0_if_exp_is_empty);
	RUN_TEST(test_split_expression_should_initialize_exps_to_single_empty_list_if_exp_is_empty);
	RUN_TEST(test_split_expression_should_initialize_exps_to_exp_if_no_separator_presented);
	RUN_TEST(test_split_expression_should_do_shallow_copy_of_list_nodes);
	RUN_TEST(test_split_expression_if_separators_are_presented);
	RUN_TEST(test_split_expression_should_handle_trailing_separator);
	RUN_TEST(test_split_expression_should_handle_precending_separator);
	RUN_TEST(test_split_expression_should_handle_inner_adjacent_separators);
	RUN_TEST(test_split_expression_should_handle_trailing_adjacent_separators);
	RUN_TEST(test_split_expression_should_handle_precending_adjacent_separators);
	return UNITY_END();
}
