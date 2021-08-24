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
	TEST_ASSERT_EQUAL(1, exps_size);
	TEST_ASSERT_NOT_NULL(exps[0].front);
	TEST_ASSERT_NOT_NULL(exps[0].back);
	TEST_ASSERT_EQUAL_PTR(exps[0].front, exps[0].back);
	TEST_ASSERT_NOT_NULL(exps[0].back->data);
	TEST_ASSERT_EQUAL_STRING("foo", exps[0].back->data);
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

		for (Node *n = exps[i].front; n != NULL; n = n->next)
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

	TEST_ASSERT_EQUAL(1, exps_size);
	TEST_ASSERT_NOT_NULL(exps[0].front);
	TEST_ASSERT_NOT_NULL(exps[0].back);
	TEST_ASSERT_EQUAL_PTR(exps[0].front, exps[0].back);
	TEST_ASSERT_NULL(exps[0].front->prev);
	TEST_ASSERT_NULL(exps[0].back->next);
	TEST_ASSERT_EQUAL_STRING("foo", exps[0].back->data);
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
	return UNITY_END();
}
