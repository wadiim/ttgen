#ifndef LOGIC_H
#define LOGIC_H

#include "list.h"

#include <stdbool.h>
#include <stddef.h>

/*
 * A logical variable.
 */
typedef struct
{
	char *name;
	bool value;
} Variable;

/*
 * A logical operator.
 */
typedef struct
{
	char *name;
	int precedence;
	int arity;
	enum
	{
		LEFT_ASSOC,
		RIGHT_ASSOC
	} associativity;
	union
	{
		bool (*unary)(bool);
		bool (*binary)(bool, bool);
	} function;
} Operator;

/*
 * Tokenizes the 'str' string.
 * The tokens are: '(', ')', ';', integers, and words (i.e. alphanumeric
 * sequences starting with non-digit).
 * Returns a list of tokens on success or NULL on error.
 */
List * tokenize(const char *str);

/*
 * Initializes the 'vars' array with variables from the 'exp' logical
 * expression. 'exp' is assumed to be the return value of the 'tokenize'
 * function. The values of the variables are initialized to 0.
 * Returns zero on success and non-zero value on error.
 */
int get_variables(const List *exp, const Operator ops[], size_t ops_len,
		Variable **vars, size_t *vars_len);

#endif /* LOGIC_H */
