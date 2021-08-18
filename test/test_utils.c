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

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_char_to_str);
	return UNITY_END();
}
