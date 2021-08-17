#include "list.h"
#include "unity.h"

#include <stdlib.h>
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

void test_List_new_should_return_empty_list(void)
{
	TEST_ASSERT_NULL(list->front);
	TEST_ASSERT_NULL(list->back);
}

void test_List_push_back_should_update_front_and_back_pointers(void)
{
	List_push_back(list, "foo");
	TEST_ASSERT_NOT_NULL(list->front);
	TEST_ASSERT_NOT_NULL(list->back);
	TEST_ASSERT_EQUAL_PTR(list->front, list->back);
}

void test_List_push_back_should_initialize_the_newly_created_node(void)
{
	List_push_back(list, "foo");
	TEST_ASSERT_EQUAL(list->front->data, list->back->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
}

void test_List_push_back_should_store_a_copy_of_str(void)
{
	char *foo = malloc(4*sizeof(char));
	strcpy(foo, "foo");
	List_push_back(list, foo);
	free(foo);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
}

void test_List_push_back_should_update_front_and_back_pointers_if_non_empty(void)
{
	List_push_back(list, "foo");
	List_push_back(list, "bar");
	TEST_ASSERT_NOT_NULL(list->front);
	TEST_ASSERT_NOT_NULL(list->back);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->data);
}

void test_List_push_back_should_update_prev_and_next_pointers(void)
{
	List_push_back(list, "foo");
	TEST_ASSERT_NULL(list->back->prev);
	TEST_ASSERT_NULL(list->back->next);
}

void test_List_push_back_should_update_prev_and_next_pointers_if_non_empty(void)
{
	List_push_back(list, "foo");
	List_push_back(list, "bar");
	List_push_back(list, "baz");

	TEST_ASSERT_NULL(list->front->prev);
	TEST_ASSERT_EQUAL_STRING("bar", list->front->next->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->next->prev->data);
	TEST_ASSERT_EQUAL_STRING("baz", list->front->next->next->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->front->next->next->prev->data);
	TEST_ASSERT_NULL(list->front->next->next->next);

	TEST_ASSERT_NULL(list->back->next);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->prev->data);
	TEST_ASSERT_EQUAL_STRING("baz", list->back->prev->next->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->back->prev->prev->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->prev->prev->next->data);
	TEST_ASSERT_NULL(list->back->prev->prev->prev);
}

void test_List_push_back_n_should_update_front_and_back_pointers(void)
{
	List_push_back_n(list, "foo", 3);
	TEST_ASSERT_NOT_NULL(list->front);
	TEST_ASSERT_NOT_NULL(list->back);
	TEST_ASSERT_EQUAL_PTR(list->front, list->back);
}

void test_List_push_back_n_should_initialize_the_newly_created_node(void)
{
	List_push_back_n(list, "foobar", 3);
	TEST_ASSERT_EQUAL(list->front->data, list->back->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
}

void test_List_push_back_n_should_store_a_copy_of_str(void)
{
	char *foo = malloc(4*sizeof(char));
	strcpy(foo, "foo");
	List_push_back_n(list, foo, 3);
	free(foo);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
}

void test_List_push_back_n_should_update_front_and_back_pointers_if_non_empty(void)
{
	List_push_back_n(list, "foo", 3);
	List_push_back_n(list, "bar", 3);
	TEST_ASSERT_NOT_NULL(list->front);
	TEST_ASSERT_NOT_NULL(list->back);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->data);
}

void test_List_push_back_n_should_update_prev_and_next_pointers(void)
{
	List_push_back_n(list, "foo", 3);
	TEST_ASSERT_NULL(list->back->prev);
	TEST_ASSERT_NULL(list->back->next);
}

void test_List_push_back_n_should_update_prev_and_next_pointers_if_non_empty(void)
{
	List_push_back_n(list, "foo", 3);
	List_push_back_n(list, "bar", 3);
	List_push_back_n(list, "baz", 3);

	TEST_ASSERT_NULL(list->front->prev);
	TEST_ASSERT_EQUAL_STRING("bar", list->front->next->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->front->next->prev->data);
	TEST_ASSERT_EQUAL_STRING("baz", list->front->next->next->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->front->next->next->prev->data);
	TEST_ASSERT_NULL(list->front->next->next->next);

	TEST_ASSERT_NULL(list->back->next);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->prev->data);
	TEST_ASSERT_EQUAL_STRING("baz", list->back->prev->next->data);
	TEST_ASSERT_EQUAL_STRING("foo", list->back->prev->prev->data);
	TEST_ASSERT_EQUAL_STRING("bar", list->back->prev->prev->next->data);
	TEST_ASSERT_NULL(list->back->prev->prev->prev);
}

void test_List_push_back_n_should_handle_count_grater_than_str_len(void)
{
	List_push_back_n(list, "foo", 22);
	TEST_ASSERT_EQUAL_STRING("foo", list->back->data);
}

void test_List_push_back_n_should_handle_count_less_than_str_len(void)
{
	List_push_back_n(list, "foobarbaz", 6);
	TEST_ASSERT_EQUAL_STRING("foobar", list->back->data);
}

void test_List_length_if_empty(void)
{
	TEST_ASSERT_EQUAL(0, List_length(list));
}

void test_List_length_if_single_node(void)
{
	List_push_back(list, "foo");
	TEST_ASSERT_EQUAL(1, List_length(list));
}

void test_List_length_if_multiple_nodes(void)
{
	List_push_back(list, "foo");
	List_push_back(list, "bar");
	List_push_back(list, "baz");
	List_push_back(list, "qux");
	TEST_ASSERT_EQUAL(4, List_length(list));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_List_new_should_return_empty_list);

	RUN_TEST(test_List_push_back_should_update_front_and_back_pointers);
	RUN_TEST(test_List_push_back_should_initialize_the_newly_created_node);
	RUN_TEST(test_List_push_back_should_store_a_copy_of_str);
	RUN_TEST(test_List_push_back_should_update_front_and_back_pointers_if_non_empty);
	RUN_TEST(test_List_push_back_should_update_prev_and_next_pointers);
	RUN_TEST(test_List_push_back_should_update_prev_and_next_pointers_if_non_empty);

	RUN_TEST(test_List_push_back_n_should_update_front_and_back_pointers);
	RUN_TEST(test_List_push_back_n_should_initialize_the_newly_created_node);
	RUN_TEST(test_List_push_back_n_should_store_a_copy_of_str);
	RUN_TEST(test_List_push_back_n_should_update_front_and_back_pointers_if_non_empty);
	RUN_TEST(test_List_push_back_n_should_update_prev_and_next_pointers);
	RUN_TEST(test_List_push_back_n_should_update_prev_and_next_pointers_if_non_empty);
	RUN_TEST(test_List_push_back_n_should_handle_count_grater_than_str_len);
	RUN_TEST(test_List_push_back_n_should_handle_count_less_than_str_len);

	RUN_TEST(test_List_length_if_empty);
	RUN_TEST(test_List_length_if_single_node);
	RUN_TEST(test_List_length_if_multiple_nodes);
	return UNITY_END();
}
