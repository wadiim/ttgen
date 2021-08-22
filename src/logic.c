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
	if (tokens == NULL) return NULL;

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
			int ret = List_push_back(tokens, t);
			free(t);
			if (ret) return NULL;
			++idx;
		}
		else
		{
			++idx;
		}

		if (token_len)
		{
			if (List_push_back_n(tokens,
					token_start, token_len))
			{
				return NULL;
			}
		}
	}

	return tokens;
}

int get_variables(const List *exp, const Operator ops[],
		size_t ops_len, Variable **vars, size_t *vars_len)
{
	*vars_len = 0;
	*vars = malloc(16*sizeof(Variable));
	if (vars == NULL) return -1;

	size_t capacity = 16;
	size_t idx = 0;

	Node* token = exp->front;
	bool found;
	while (token)
	{
		found = false;
		for (size_t i = 0; i < ops_len; ++i)
		{
			if (strcmp(token->data, ops[i].name) == 0)
			{
				found = true;
				break;
			}
		}

		if (found == false)
		{
			if (idx >= capacity-1)
			{
				*vars = realloc(*vars,
						2*capacity*sizeof(Variable));
				if (*vars == NULL) return -3;
				capacity *= 2;
			}
			(*vars)[idx].name = token->data;
			(*vars)[idx].value = 0;
			++idx;
		}

		token = token->next;
	}
	*vars_len = idx;
	*vars = realloc(*vars, (*vars_len)*sizeof(Variable));
	if (*vars == NULL) return -4;

	return 0;
}
