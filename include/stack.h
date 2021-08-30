#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct
{
	char **data;
	size_t size;
	size_t capacity;
} Stack;

/*
 * Returns a pointer to a newly created stack.
 */
Stack * Stack_new(void);

/*
 * Frees an entire stack.
 */
void Stack_free(Stack *stack);

/*
 * Push the 'str' at the top of the 'stack'.
 */
int Stack_push(Stack *stack, const char *str);

/*
 * Returns the string at the top of the stack or NULL if the stack is
 * empty. The resulting string should not be freed by the caller.
 */
char * Stack_top(Stack *stack);

/*
 * Returns the string at the top of the stack and removes it from the
 * stack. The resulting string should be freed by the caller.
 */
char * Stack_pop(Stack *stack);

#endif /* STACK_H */
