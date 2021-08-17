#ifndef LIST_H
#define LIST_H

#include <stddef.h>

/*
 * A doubly linked list node.
 */
typedef struct Node
{
	char *data;
	struct Node *prev;
	struct Node *next;
} Node;

/*
 * A doubly linked list.
 */
typedef struct List
{
	Node *front;
	Node *back;
} List;

/*
 * Returns a pointer to a newly created linked list.
 */
List * List_new(void);

/*
 * Frees an entire list.
 */
void List_free(List *list);

/*
 * Adds a node at the end of 'list' and initializes it with 'str'.
 * Returns zero on success and non-zero value on error.
 */
int List_push_back(List *list, const char *str);

/*
 * Adds a node at the end of 'list' and initializes it with 'count'
 * characters of the character array pointed to by 'str'.
 * Returns zero on success and non-zero value on error.
 */
int List_push_back_n(List *list, const char *str, size_t count);

/*
 * Returns the length of 'list'.
 */
size_t List_length(const List *list);

#endif /* LIST_H */
