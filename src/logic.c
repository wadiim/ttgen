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

bool update_variables(Variable vars[], size_t vars_len)
{
	if (vars_len)
	{
		bool carry_flag = 0;
		size_t i = vars_len-1;
		while (true)
		{
			carry_flag = vars[i].value;
			vars[i].value = !vars[i].value;
			if (carry_flag == 0) return true;
			if (i == 0) break;
			--i;
		}
	}
	// If we got here, then all values were 1.
	// Reset variables to their initial state.
	for (size_t i = 0; i < vars_len; ++i) vars[i].value = 1;

	return false;
}

int split_expression(List *exp, List **exps, size_t *exps_len)
{
	*exps = malloc(8*sizeof(List));
	if (*exps == NULL) return -1;
	(*exps)[0].front = exp->front;
	size_t capacity = 8, idx = 0;
	Node *node = exp->front;

	while (node)
	{
		if (strcmp(node->data, ";") == 0)
		{
			if (idx + 1 >= capacity - 1)
			{
				*exps = realloc(*exps, 2*capacity*sizeof(List));
				if (*exps == NULL) return -2;
				capacity *= 2;
			}
			
			if (node == exp->back)
			{
				exp->back = exp->back->prev;
				free(exp->back->next->data);
				free(exp->back->next);
				exp->back->next = NULL;
				node = NULL;
			}
			else
			{
				(*exps)[idx].back = node->prev;
				(*exps)[idx+1].front = node->next;
				node = node->next;
				free(node->prev->data);
				free(node->prev);
				(*exps)[idx].back->next = NULL;
				(*exps)[idx+1].front->prev = NULL;
				++idx;
			}
		}
		else
		{
			node = node->next;
		}
	}
	(*exps)[idx].back = exp->back;
	*exps_len = idx + 1;

	return 0;
}
