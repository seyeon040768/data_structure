#pragma once

#include <stdio.h>
#include <assert.h>

#define MAX_QUEUE_SIZE 8

typedef struct
{
	int front;
	int rear;
	int elements[MAX_QUEUE_SIZE];
} Queue;

int IsFullQueue(const Queue* queue)
{
	return (queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE);
}

int IsEmptyQueue(const Queue* queue)
{
	return (queue->front == queue->rear);
}

void Enqueue(Queue* queue, int value)
{
	assert(!IsFullQueue(queue));

	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	queue->elements[queue->rear] = value;
}

int Dequeue(Queue* queue)
{
	assert(!IsEmptyQueue(queue));

	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	return queue->elements[queue->front];
}

int Peek(Queue* queue)
{
	assert(!IsEmptyQueue(queue));

	return queue->elements[(queue->front + 1) % MAX_QUEUE_SIZE];
}