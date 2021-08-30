#include "queue.h"

#include <stdlib.h>
#include <string.h>

Queue * Queue_new(void)
{
	Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL) return NULL;
	queue->front = queue->back = NULL;
	return queue;
}

void Queue_free(Queue *queue)
{
	QNode *tmp;
	while (queue->front)
	{
		tmp = queue->front;
		queue->front = queue->front->next;
		free(tmp);
	}
	free(queue);
}

int Queue_push(Queue *queue, const char *str)
{
	QNode *node = malloc(sizeof(QNode));
	if (node == NULL) return -1;
	node->data = malloc((strlen(str) + 1)*sizeof(char));
	if (node->data == NULL) return -2;
	node->next = NULL;
	strcpy(node->data, str);
	if (queue->front == NULL && queue->back == NULL)
	{
		queue->front = queue->back = node;
	}
	else if (queue->back)
	{
		queue->back->next = node;
		queue->back = node;
	}
	return 0;
}

char * Queue_pop(Queue *queue)
{
	if (queue->front == NULL) return NULL;

	QNode *tmp = queue->front;
	queue->front = queue->front->next;

	if (queue->front == NULL) queue->back = NULL;

	char *ret = tmp->data;
	free(tmp);

	return ret;
}
