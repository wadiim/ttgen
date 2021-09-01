#include "list.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

List * List_new(void)
{
	List *list = malloc(sizeof(List));
	if (list) list->front = list->back = NULL;
	return list;
}

void List_free(List *list)
{
	LNode *tmp;
	while (list->front)
	{
		tmp = list->front;
		list->front = list->front->next;
		free(tmp);
	}
	free(list);
}

int List_push_back(List *list, const char *str)
{
	LNode *node = malloc(sizeof(LNode));
	if (node == NULL) return -1;
	node->data = malloc((strlen(str) + 1)*sizeof(char));
	if (node->data == NULL) return -2;
	strcpy(node->data, str);
	node->next = NULL;
	node->prev = list->back;
	if (list->front == NULL && list->back == NULL)
	{
		list->front = list->back = node;
	}
	else if (list->back)
	{
		list->back->next = node;
		list->back = node;
	}
	return 0;
}

int List_push_back_n(List *list, const char *str, size_t count)
{
	char *tmp = malloc((count + 1)*sizeof(char));
	if (tmp == NULL) return -3;
	strncpy(tmp, str, count);
	tmp[count] = '\0';
	int retval = List_push_back(list, tmp);
	free(tmp);
	return retval;
}

size_t List_length(const List *list)
{
	size_t len = 0;
	for (LNode *node = list->front; node != NULL; node = node->next)
	{
		++len;
	}
	return len;
}
