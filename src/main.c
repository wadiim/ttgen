#include "logic.h"

#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_NAME "ttgen"

/*
 * Prints an error message and exits with non-zero status.
 */
static void die(const char *msg);

/*
 * Returns a line read from stdin.
 */
char * get_line(void);

/*
 * Draws n spaces on stdout.
 */
void draw_n_spaces(size_t n);

int main(void)
{
	// Define operators.
	Operator ops[] =
	{
		{
			.name = "NOT",
			.precedence = 1,
			.arity = 1,
			.associativity = RIGHT_ASSOC,
			.function.unary = logical_not
		},
		{
			.name = "AND",
			.precedence = 2,
			.arity = 2,
			.associativity = LEFT_ASSOC,
			.function.binary = logical_and
		},
		{
			.name = "OR",
			.precedence = 3,
			.arity = 2,
			.associativity = LEFT_ASSOC,
			.function.binary = logical_or
		},
		{
			.name = "XOR",
			.precedence = 4,
			.arity = 2,
			.associativity = LEFT_ASSOC,
			.function.binary = logical_xor
		},
		{
			.name = "IMPLY",
			.precedence = 5,
			.arity = 2,
			.associativity = RIGHT_ASSOC,
			.function.binary = logical_imply
		},
		{
			.name = "XNOR",
			.precedence = 6,
			.arity = 2,
			.associativity = RIGHT_ASSOC,
			.function.binary = logical_xnor
		}
	};
	size_t ops_len = 6;

	while (true)
	{
		// Read input.
		char *input = get_line();
		if (input == NULL) die("Failed to read input");
		if (strcmp(input, "") == 0 || strcmp(input, "\n") == 0)
		{
			free(input);
			if (feof(stdin)) break;
			else continue;
		}

		// Tokenize input.
		List *tokens = tokenize(input);
		if (tokens == NULL) die("Failed to tokenize input");

		// Extract variables.
		Variable *vars;
		size_t vars_len;
		if (get_variables(tokens, ops, ops_len, &vars, &vars_len) != 0)
		{
			die("Failed to extract variables from tokens");
		}

		// Split compound expression.
		List *exps;
		size_t exps_len;
		if (split_expression(tokens, &exps, &exps_len) != 0)
		{
			die("Failed to split tokens into expressions");
		}

		// Convert expressions to strings.
		char **exp_strs = malloc((exps_len + 1)*sizeof(char *));
		if (exp_strs == NULL)
		{
			die("Failed to allocate memory for expression strings");
		}
		for (size_t i = 0; i < exps_len; ++i)
		{
			exp_strs[i] = expression_to_str(&exps[i]);
			if (exp_strs[i] == NULL)
			{
				die("Failed to convert expression to string");
			}
		}

		// Convert expressions to postfix.
		Queue **postfix_exps = malloc(exps_len*sizeof(Queue *));
		if (postfix_exps == NULL)
		{
			die("Failed to allocate memory for postfix expressions");
		}
		for (size_t i = 0; i < exps_len; ++i)
		{
			if (infix_to_postfix(&exps[i], ops, ops_len, &postfix_exps[i]) != 0)
			{
				die("Failed to convert expression from infix to postfix notation");
			}
		}

		// Calculate the number of table columns.
		size_t cols_num = vars_len + exps_len;

		// Calculate column content widths.
		size_t *widths = malloc((cols_num)*sizeof(size_t));
		if (widths == NULL)
		{
			die("Failed to store the widths of columns content");
		}
		for (size_t i = 0; i < vars_len; ++i)
		{
			widths[i] = strlen(vars[i].name);
		}
		for (size_t i = 0; i < exps_len; ++i)
		{
			widths[i+vars_len] = strlen(exp_strs[i]);
		}

		// Generate the row separator.
		size_t line_sep_len = 1;
		for (size_t i = 0; i < cols_num; ++i)
		{
			line_sep_len += widths[i] + 3;
		}
		char *line_sep = malloc((line_sep_len + 1)*sizeof(char));
		if (line_sep == NULL)
		{
			die("Failed to allocate memory for the row separator");
		}
		line_sep[0] = '+';
		for (size_t i = 1, col = 0; i < line_sep_len && col < cols_num; ++col)
		{
			for (size_t j = 0; j < widths[col] + 2; ++j)
			{
				line_sep[i++] = '-';
			}
			line_sep[i++] = '+';
		}
		line_sep[line_sep_len] = '\0';

		// Draw the table header.
		printf("%s\n|", line_sep);
		for (size_t i = 0; i < vars_len; ++i)
		{
			printf(" %s |", vars[i].name);
		}
		for (size_t i = 0; i < exps_len; ++i)
		{
			printf(" %s |", exp_strs[i]);
			free(exp_strs[i]);
		}
		printf("\n%s\n", line_sep);

		// Draw the table body.
		do
		{
			printf("|");
			for (size_t i = 0; i < cols_num; ++i)
			{
				draw_n_spaces((widths[i] / 2) + ((widths[i] % 2) ? 1 : 0));
				if (i < vars_len)
				{
					printf("%d", vars[i].value);
				}
				else
				{
					Queue *evaluated_exp = evaluate_expression(
							postfix_exps[i-vars_len], vars, vars_len);
					if (evaluated_exp == NULL)
					{
						die("Failed to evaluate expression");
					}
					bool result = calculate(evaluated_exp, ops, ops_len);
					printf("%d", result);
					free(evaluated_exp);
				}
				draw_n_spaces((widths[i] / 2) + 1);
				printf("|");
			}
			printf("\n%s\n", line_sep);
		}
		while (update_variables(vars, vars_len));

		// Free up memory.
		free(line_sep);
		free(widths);
		for (size_t i = 0; i < exps_len; ++i) Queue_free(postfix_exps[i]);
		free(postfix_exps);
		free(exp_strs);
		List_free(exps);
		free(vars);
		free(input);
	}

	return EXIT_SUCCESS;
}

static void die(const char *msg)
{
	if (errno == 0)
	{
		fprintf(stderr, "%s: %s\n", PROGRAM_NAME, msg);
	}
	else
	{
		fprintf(stderr, "%s: %s: %s\n", PROGRAM_NAME, msg,
				strerror(errno));
	}
	exit(EXIT_FAILURE);
}

char * get_line(void)
{
	char *line = malloc(128);
	size_t capacity = 128;
	size_t len = 0;
	int c;

	if (line == NULL) return NULL;

	while (true)
	{
		c = fgetc(stdin);
		if (c == EOF)
		{
			ungetc(c, stdin);
			break;
		}

		if ((line[len++] = c) == '\n') break;

		if (len >= capacity + 1)
		{
			char * tmp = realloc(line, capacity *= 2);
			if (tmp == NULL)
			{
				free(line);
				return NULL;
			}
		}
	}

	line[len] = '\0';
	return line;
}

void draw_n_spaces(size_t n)
{
	char *output = malloc((n + 1)*sizeof(char));
	output[n] = '\0';
	while (n) output[--n] = ' ';
	printf("%s", output);
	free(output);
}
