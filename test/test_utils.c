#include "unity.h"
#include "utils.h"

#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_char_to_str(void)
{
	char *c = char_to_str('$');
	TEST_ASSERT_EQUAL_STRING("$", c);
	free(c);
}

void test_strcicmp_if_equal_strings(void)
{
	char a[] = "foo";
	char b[] = "foo";
	TEST_ASSERT_EQUAL_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_not_equal_strings(void)
{
	char a[] = "foo";
	char b[] = "bar";
	TEST_ASSERT_NOT_EQUAL_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_equal_but_different_case(void)
{
	char a[] = "foo";
	char b[] = "FOO";
	TEST_ASSERT_EQUAL_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_equal_but_mixed_case(void)
{
	char a[] = "foo";
	char b[] = "FoO";
	TEST_ASSERT_EQUAL_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_a_less_than_b(void)
{
	char a[] = "bar";
	char b[] = "foo";
	TEST_ASSERT_LESS_THAN_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_a_greater_than_b(void)
{
	char a[] = "foo";
	char b[] = "bar";
	TEST_ASSERT_GREATER_THAN_INT(0, strcicmp(a, b));
}

void test_strcicmp_if_a_is_null(void)
{
	char b[] = "foo";
	TEST_ASSERT_LESS_THAN_INT(0, strcicmp(NULL, b));
}

void test_strcicmp_if_b_is_null(void)
{
	char a[] = "foo";
	TEST_ASSERT_GREATER_THAN_INT(0, strcicmp(a, NULL));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_char_to_str);
	RUN_TEST(test_strcicmp_if_equal_strings);
	RUN_TEST(test_strcicmp_if_not_equal_strings);
	RUN_TEST(test_strcicmp_if_equal_but_different_case);
	RUN_TEST(test_strcicmp_if_equal_but_mixed_case);
	RUN_TEST(test_strcicmp_if_a_less_than_b);
	RUN_TEST(test_strcicmp_if_a_greater_than_b);
	RUN_TEST(test_strcicmp_if_a_is_null);
	RUN_TEST(test_strcicmp_if_b_is_null);
	return UNITY_END();
}
