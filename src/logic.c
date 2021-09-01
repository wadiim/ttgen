#include "logic.h"
#include "stack.h"
#include "utils.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool logical_not(bool a)
{
	return !a;
}

bool logical_and(bool a, bool b)
{
	return a && b;
}

bool logical_or(bool a, bool b)
{
	return a || b;
}

bool logical_xor(bool a, bool b)
{
	return !(a == b);
}

bool logical_imply(bool a, bool b)
{
	return !a || b;
}

int str_to_operator_idx(const char* name, const Operator ops[],
		size_t ops_len)
{
	if (name == NULL) return -1;
	for (int i = 0; i < ops_len; ++i)
	{
		if (strcicmp(name, ops[i].name) == 0) return i;
	}
	return -2;
}

int str_to_variable_idx(const char *name, const Variable vars[],
		size_t vars_len)
{
	if (name == NULL) return -1;
	for (int i = 0; i < vars_len; ++i)
	{
		if (strcmp(name, vars[i].name) == 0) return i;
	}
	return -2;
}

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

	LNode* token = exp->front;
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
	size_t capacity = 8, idx = 0;

	// Remove precending separators.
	while (exp && exp->front && strcmp(exp->front->data, ";") == 0)
	{
		exp->front = exp->front->next;
		free(exp->front->prev->data);
		free(exp->front->prev);
		exp->front->prev = NULL;
	}

	// Remove trailing separators.
	while (exp && exp->back && strcmp(exp->back->data, ";") == 0)
	{
		exp->back = exp->back->prev;
		free(exp->back->next->data);
		free(exp->back->next);
		exp->back->next = NULL;
	}

	(*exps)[0].front = exp->front;
	LNode *node = exp->front;

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
			
			size_t num_of_sep = 1;
			LNode *tmp = node->next;
			while (strcmp(tmp->data, ";") == 0)
			{
				++num_of_sep;
				tmp = tmp->next;
			}

			(*exps)[idx].back = node->prev;
			(*exps)[idx].back->next = NULL;
			for (size_t i = 0; i < num_of_sep; ++i)
			{
				node = node->next;
				free(node->prev->data);
				free(node->prev);
			}
			(*exps)[idx+1].front = node;
			(*exps)[idx+1].front->prev = NULL;
			++idx;
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

int infix_to_postfix(const List *exp, const Operator ops[],
		size_t ops_len, Queue **postfix)
{
	if (exp == NULL)
	{
		postfix = NULL;
		return -1;
	}

	*postfix = Queue_new();
	Stack *op_stack = Stack_new();

	for (LNode *token = exp->front; token; token = token->next)
	{
		if (strcmp(token->data, "(") == 0)
		{
			Stack_push(op_stack, token->data);
		}
		else if (strcmp(token->data, ")") == 0)
		{
			while (op_stack->size > 0 && strcmp(Stack_top(op_stack), "(") != 0)
			{
				Queue_push(*postfix, Stack_pop(op_stack));
			}
			if (op_stack->size == 0)
			{
				// Too few opening parentheses.
				Stack_free(op_stack);
				return -1;
			}
			Stack_pop(op_stack);
		}
		else
		{
			int curr_op_idx = str_to_operator_idx(
					token->data, ops, ops_len);
			if (curr_op_idx >= 0)
			{
				// Handle operator.
				int top_op_idx;
				while (true)
				{
					top_op_idx = str_to_operator_idx(Stack_top(op_stack), ops, ops_len);
					if (top_op_idx >= 0 && (ops[top_op_idx].precedence < ops[curr_op_idx].precedence || ops[top_op_idx].precedence == ops[curr_op_idx].precedence && ops[curr_op_idx].associativity == LEFT_ASSOC))
					{
						Queue_push(*postfix, Stack_pop(op_stack));
					}
					else
					{
						break;
					}
				}
				Stack_push(op_stack, token->data);
			}
			else
			{
				// Handle variable.
				Queue_push(*postfix, token->data);
			}
		}
	}

	while (op_stack->size > 0)
	{
		if (strcmp(Stack_top(op_stack), "(") == 0
				|| strcmp(Stack_top(op_stack), ")") == 0)
		{
			// Mismatched parentheses.
			Stack_free(op_stack);
			return -2;
		}
		Queue_push(*postfix, Stack_pop(op_stack));
	}
	Stack_free(op_stack);

	return 0;
}

List * evaluate_expression(const List *exp, const Variable vars[],
		size_t vars_len)
{
	if (exp == NULL) return NULL;

	List *ret = List_new();

	for (LNode *node = exp->front; node; node = node->next)
	{
		int idx = str_to_variable_idx(node->data, vars, vars_len);
		if (idx >= 0)
		{
			char *val = char_to_str('0' + vars[idx].value);
			List_push_back(ret, val);
		}
		else
		{
			List_push_back(ret, node->data);
		}
	}

	return ret;
}

char * expression_to_str(const List *exp)
{
	if (exp == NULL) return NULL;

	char *ret;
	if (exp->back == NULL || exp->back->data == NULL)
	{
		ret = malloc(sizeof(char));
		ret[0] = '\0';
	}
	else
	{
		ret = malloc(64*sizeof(char));
		size_t capacity = 64;
		size_t ret_len = 0;

		for (LNode *node = exp->front; node; node = node->next)
		{
			size_t token_len = strlen(node->data);
			while (token_len + 2 >= capacity - ret_len)
			{
				char *tmp = realloc(ret,
						2*capacity*sizeof(char));
				if (tmp == NULL) return NULL;
				ret = tmp;
				capacity *= 2;
			}
			if (ret_len > 0 && strcmp(")", node->data) != 0
					&& strcmp("(", node->prev->data)
					!= 0)
			{
				strcpy(ret + ret_len, " ");
				++ret_len;
			}
			strcpy(ret + ret_len, node->data);
			ret_len += token_len;
		}
	}

	return ret;
}

bool calculate(const List *exp, const Operator ops[], size_t ops_len)
{
	Stack *stack = Stack_new();

	for (LNode *node = exp->front; node; node = node->next)
	{
		int op_idx =
			str_to_operator_idx(node->data, ops, ops_len);
		if (op_idx < 0)
		{
			Stack_push(stack, node->data);
			continue;
		}
		else if (ops[op_idx].arity == 1)
		{
			bool x = !!atoi(Stack_pop(stack));
			bool v = ops[op_idx].function.unary(x);
			Stack_push(stack, v ? "1" : "0");
		}
		else if (ops[op_idx].arity == 2)
		{
			bool y = !!atoi(Stack_pop(stack));
			bool x = !!atoi(Stack_pop(stack));
			bool v = ops[op_idx].function.binary(x, y);
			Stack_push(stack, v ? "1" : "0");
		}
	}

	bool ret = stack->size ? !!atoi(Stack_pop(stack)) : 1;
	Stack_free(stack);

	return ret;
}
