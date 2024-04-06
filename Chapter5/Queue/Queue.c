#include <stdio.h>
#include <assert.h>

#define MAX_QUEUE_SIZE 100

typedef struct
{
	int front;
	int rear;
	int elements[MAX_QUEUE_SIZE];
} Queue;

int IsFull(const Queue* queue)
{
	return (queue->rear == MAX_QUEUE_SIZE - 1);
}

int IsEmpty(const Queue* queue)
{
	return (queue->front == queue->rear);
}

void Enqueue(Queue* queue, int value)
{
	assert(!IsFull(queue));

	queue->elements[++(queue->rear)] = value;
}

int Dequeue(Queue* queue)
{
	assert(!IsEmpty(queue));

	return queue->elements[++(queue->front)];
}

int Peek(Queue* queue)
{
	assert(!IsEmpty(queue));

	return queue->elements[queue->front + 1];
}

int main(void)
{
	Queue queue = { .front = -1, .rear = -1 };

	Enqueue(&queue, 3);
	Enqueue(&queue, 1);

	printf("%d\n", Dequeue(&queue));

	return 0;
}