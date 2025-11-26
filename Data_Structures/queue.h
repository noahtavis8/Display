#ifndef __QUEUE_H
#define __QUEUE_H

/*
 * Structure used to represent a queue.
 */
struct queue;

/*
 * Queue interface function prototypes.  Refer to queue.c for documentation
 * about each of these functions.
 */
struct queue* queue_create();
void queue_free(struct queue* queue);
int queue_isempty(struct queue* queue);
void queue_enqueue(struct queue* queue, void* val);
void* queue_front(struct queue* queue);
void* queue_dequeue(struct queue* queue);
int queue_length(struct queue* queue);
#endif
