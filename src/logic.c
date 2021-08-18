#include "logic.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

List * tokenize(const char *str)
{
	size_t token_len = 0;
	const char *token_start = NULL;
	List *tokens = List_new();

	size_t idx = 0;
	size_t str_len = strlen(str);
	while (idx < str_len)
	{
		token_len = 0;
		token_start = str + idx;
		if (isdigit(str[idx]))
		{
			while (isdigit(str[idx]))
			{
				++token_len;
				++idx;
			}
		}
		else if (isalpha(str[idx]))
		{
			while (isalnum(str[idx]))
			{
				++token_len;
				++idx;
			}
		}
		else if (str[idx] == '(' || str[idx] == ')'
				|| str[idx] == ';')
		{
			char *t = char_to_str(str[idx]);
			List_push_back(tokens, t);
			free(t);
			++idx;
		}
		else
		{
			++idx;
		}

		if (token_len)
		{
			List_push_back_n(tokens, token_start, token_len);
		}
	}

	return tokens;
}
