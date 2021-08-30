#include "queue.h"
#include "unity.h"

#include <stdlib.h>
#include <string.h>

Queue *queue;

void setUp(void)
{
	queue = Queue_new();
}

void tearDown(void)
{
	Queue_free(queue);
}

void test_Queue_new_should_return_empty_queue(void)
{
	TEST_ASSERT_NOT_NULL(queue);
	TEST_ASSERT_NULL(queue->front);
	TEST_ASSERT_NULL(queue->back);
}

void test_Queue_push_should_add_str_at_the_end_of_queue_if_empty(void)
{
	Queue_push(queue, "foo");
	TEST_ASSERT_NOT_NULL(queue->front);
	TEST_ASSERT_NOT_NULL(queue->back);
	TEST_ASSERT_EQUAL_PTR(queue->front, queue->back);
	TEST_ASSERT_EQUAL_STRING("foo", queue->back->data);
}

void test_Queue_push_should_add_str_at_the_end_of_queue_if_non_empty(void)
{
	Queue_push(queue, "foo");
	Queue_push(queue, "bar");
	TEST_ASSERT_NOT_NULL(queue->front);
	TEST_ASSERT_NOT_NULL(queue->back);
	TEST_ASSERT_EQUAL_STRING("foo", queue->front->data);
	TEST_ASSERT_EQUAL_STRING("bar", queue->back->data);
}

void test_Queue_push_should_save_copy_of_str(void)
{
	char *str = malloc(4*sizeof(char));
	strcpy(str, "foo");
	Queue_push(queue, str);
	free(str);
	TEST_ASSERT_EQUAL_STRING("foo", queue->back->data);
}

void test_Queue_pop_should_return_null_if_empty(void)
{
	TEST_ASSERT_NULL(Queue_pop(queue));
}

void test_Queue_pop_should_remove_the_first_element_if_single_element(void)
{
	Queue_push(queue, "foo");
	Queue_pop(queue);
	TEST_ASSERT_NULL(queue->back);
	TEST_ASSERT_NULL(queue->front);
}

void test_Queue_pop_should_remove_the_first_element_if_multiple_elements(void)
{
	Queue_push(queue, "foo");
	Queue_push(queue, "bar");
	Queue_push(queue, "baz");
	Queue_pop(queue);
	TEST_ASSERT_NOT_NULL(queue->front);
	TEST_ASSERT_NOT_NULL(queue->back);
	TEST_ASSERT_EQUAL_STRING("bar", queue->front->data);
	TEST_ASSERT_EQUAL_STRING("baz", queue->back->data);
}

void test_Queue_pop_should_return_the_first_element(void)
{
	Queue_push(queue, "foo");
	Queue_push(queue, "bar");
	TEST_ASSERT_EQUAL_STRING("foo", Queue_pop(queue));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_Queue_new_should_return_empty_queue);
	RUN_TEST(test_Queue_push_should_add_str_at_the_end_of_queue_if_empty);
	RUN_TEST(test_Queue_push_should_add_str_at_the_end_of_queue_if_non_empty);
	RUN_TEST(test_Queue_push_should_save_copy_of_str);
	RUN_TEST(test_Queue_pop_should_return_null_if_empty);
	RUN_TEST(test_Queue_pop_should_remove_the_first_element_if_single_element);
	RUN_TEST(test_Queue_pop_should_remove_the_first_element_if_multiple_elements);
	RUN_TEST(test_Queue_pop_should_return_the_first_element);
	return UNITY_END();
}
