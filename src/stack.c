#include "stack.h"

#include <stdlib.h>
#include <string.h>

Stack * Stack_new(void)
{
	Stack *stack = malloc(sizeof(Stack));
	if (stack == NULL) return NULL;
	stack->size = 0;
	stack->data = malloc(64*sizeof(char*));
	if (stack->data) stack->capacity = 64;
	else stack->capacity = 0;
	return stack;
}

void Stack_free(Stack *stack)
{
	for (size_t i = 0; i < stack->size; ++i) free(stack->data[i]);
	free(stack->data);
	free(stack);
}

int Stack_push(Stack *stack, const char *str)
{
	if (stack->size >= stack->capacity)
	{
		char **tmp = realloc(stack->data,
				2*stack->capacity*sizeof(char*));
		if (tmp == NULL) return -1;
		stack->data = tmp;
		stack->capacity *= 2;
	}
	stack->data[stack->size] =
		malloc((strlen(str) + 1)*sizeof(char));
	if (stack->data[stack->size] == NULL) return -2;
	strcpy(stack->data[stack->size], str);
	++stack->size;
	return 0;
}

char * Stack_top(Stack *stack)
{
	if (stack->size == 0) return NULL;
	return stack->data[stack->size-1];
}

char * Stack_pop(Stack *stack)
{
	if (stack->size == 0) return NULL;
	return stack->data[--stack->size];
}
