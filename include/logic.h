#ifndef LOGIC_H
#define LOGIC_H

#include "list.h"
#include "queue.h"

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
 * Logical operations.
 */
bool logical_not(bool a);
bool logical_and(bool a, bool b);
bool logical_or(bool a, bool b);
bool logical_xor(bool a, bool b);
bool logical_imply(bool a, bool b);
bool logical_xnor(bool a, bool b);

/*
 * Returns an index of the operator with a name matching 'name' or
 * negative value if there is no such operator. Treats the operator
 * names as case insensitive.
 */
int str_to_operator_idx(const char *name, const Operator ops[],
		size_t ops_len);

/*
 * Returns the index of the variable with a name matching 'name' or
 * negative value if there is no such variable. Treats the variable
 * names as case sensitive.
 */
int str_to_variable_idx(const char *name, const Variable vars[],
		size_t vars_len);

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

/*
 * Updates the values of 'vars'. This function treats the values as
 * sequential digits of a binary number and increments that number on
 * each call. Returns false if that number cannot be further
 * incremented and true otherwise.
 */
bool update_variables(Variable vars[], size_t vars_len);

/*
 * Split 'exp' into multiple expressions using the ';' token as a
 * separator. 'exp' is assumed to be the return value of the 'tokenize'
 * function. 'exp' should not be used or freed after passing it to this
 * function. The ';' tokens are excluded from the resulting expressions.
 * Returns zero on success and non-zero value on error.
 */
int split_expression(List *exp, List **exps, size_t *exps_len);

/*
 * Converts 'exp' from infix to postfix notation (more specifically
 * the Reverse Polish notation) using Shunting-yard algorithm.
 * Returns zero on success and non-zero value on error.
 */
int infix_to_postfix(const List *exp, const Operator ops[],
		size_t ops_len, Queue **postfix);

/*
 * Returns evaluated 'exp', i.e. an expression in which all variable
 * names are replaced with their values.
 */
Queue * evaluate_expression(const Queue *exp, const Variable vars[],
		size_t vars_len);

/*
 * Returns the string representation of the 'exp' expression on
 * success and null on error. The returned string is dynamically
 * allocated, null-terminated, and should be freed by the caller.
 */
char * expression_to_str(const List *exp);

/*
 * Calculates the 'exp' logical expression and returns the result.
 * 'exp' is expected to be in the evaluated postfix form.
 */
bool calculate(const Queue *exp, const Operator ops[], size_t ops_len);

#endif /* LOGIC_H */
