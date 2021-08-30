#include "stack.h"
#include "unity.h"

#include <stdlib.h>
#include <string.h>

Stack *stack;

void setUp(void)
{
	stack = Stack_new();
}

void tearDown(void)
{
	Stack_free(stack);
}

void test_Stack_new_should_return_empty_stack(void)
{
	TEST_ASSERT_EQUAL(0, stack->size);
}

void test_Stack_push_should_update_size(void)
{
	Stack_push(stack, "foo");
	TEST_ASSERT_EQUAL(1, stack->size);
	Stack_push(stack, "bar");
	TEST_ASSERT_EQUAL(2, stack->size);
}

void test_Stack_push_should_add_str_at_the_end_of_arr(void)
{
	Stack_push(stack, "foo");
	Stack_push(stack, "bar");
	TEST_ASSERT_EQUAL_STRING("foo", stack->data[0]);
	TEST_ASSERT_EQUAL_STRING("bar", stack->data[1]);
}

void test_Stack_push_should_save_copy_of_str(void)
{
	char *str = malloc(4*sizeof(char));
	strcpy(str, "foo");
	Stack_push(stack, str);
	free(str);
	TEST_ASSERT_EQUAL_STRING("foo", stack->data[0]);
}

void test_Stack_top_should_not_update_size(void)
{
	Stack_push(stack, "foo");
	TEST_ASSERT_EQUAL(1, stack->size);
	Stack_top(stack);
	TEST_ASSERT_EQUAL(1, stack->size);
}

void test_Stack_top_should_return_null_if_empty(void)
{
	TEST_ASSERT_NULL(Stack_top(stack));
}

void test_Stack_top_should_return_top_element(void)
{
	Stack_push(stack, "foo");
	TEST_ASSERT_EQUAL_STRING("foo", Stack_top(stack));
	Stack_push(stack, "bar");
	TEST_ASSERT_EQUAL_STRING("bar", Stack_top(stack));
}

void test_Stack_pop_should_update_size(void)
{
	Stack_push(stack, "foo");
	Stack_push(stack, "bar");
	TEST_ASSERT_EQUAL(2, stack->size);
	Stack_pop(stack);
	TEST_ASSERT_EQUAL(1, stack->size);
	Stack_pop(stack);
	TEST_ASSERT_EQUAL(0, stack->size);
}

void test_Stack_pop_should_return_null_if_empty(void)
{
	TEST_ASSERT_NULL(Stack_pop(stack));
}

void test_Stack_pop_should_return_top_element(void)
{
	Stack_push(stack, "foo");
	Stack_push(stack, "bar");
	TEST_ASSERT_EQUAL_STRING("bar", Stack_pop(stack));
	TEST_ASSERT_EQUAL_STRING("foo", Stack_pop(stack));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_Stack_new_should_return_empty_stack);
	RUN_TEST(test_Stack_push_should_update_size);
	RUN_TEST(test_Stack_push_should_add_str_at_the_end_of_arr);
	RUN_TEST(test_Stack_push_should_save_copy_of_str);
	RUN_TEST(test_Stack_top_should_not_update_size);
	RUN_TEST(test_Stack_top_should_return_null_if_empty);
	RUN_TEST(test_Stack_top_should_return_top_element);
	RUN_TEST(test_Stack_pop_should_update_size);
	RUN_TEST(test_Stack_pop_should_return_null_if_empty);
	RUN_TEST(test_Stack_pop_should_return_top_element);
	return UNITY_END();
}
