#ifndef QUEUE_H
#define QUEUE_H

/*
 * A linked list node to store a queue entry.
 */
typedef struct QNode
{
	char *data;
	struct QNode *next;
} QNode;

/*
 * A linked list implementation of the queue data structure.
 */
typedef struct
{
	QNode *front;
	QNode *back;
} Queue;

/*
 * Returns a pointer to a newly created queue.
 */
Queue * Queue_new(void);

/*
 * Frees an entire queue.
 */
void Queue_free(Queue *queue);

/*
 * Adds a node at the end of 'queue' and initializes it with 'str'.
 */
int Queue_push(Queue *queue, const char *str);

/*
 * Returns the string at the end of the queue and removes it from the
 * queue. The resulting string should be freed by the caller.
 */
char * Queue_pop(Queue *queue);

#endif /* QUEUE_H */
