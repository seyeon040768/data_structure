#include <stdio.h>
#include <assert.h>

#define MAX_QUEUE_SIZE 8

typedef struct
{
	int front;
	int rear;
	int elements[MAX_QUEUE_SIZE];
} CircularQueue;

int IsFull(const CircularQueue* queue)
{
	return (queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE);
}

int IsEmpty(const CircularQueue* queue)
{
	return (queue->front == queue->rear);
}

void Enqueue(CircularQueue* queue, int value)
{
	assert(!IsFull(queue));

	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	queue->elements[queue->rear] = value;
}

int Dequeue(CircularQueue* queue)
{
	assert(!IsEmpty(queue));

	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	return queue->elements[queue->front];
}

int Peek(CircularQueue* queue)
{
	assert(!IsEmpty(queue));

	return queue->elements[(queue->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
	CircularQueue queue = { .front = 0, .rear = 0 };

	Enqueue(&queue, 3);
	Enqueue(&queue, 1);
	Enqueue(&queue, 3);
	Enqueue(&queue, 1);
	Enqueue(&queue, 3);
	Enqueue(&queue, 1);
	Enqueue(&queue, 3);
	//Enqueue(&queue, 1);

	Dequeue(&queue);
	Dequeue(&queue);
	Dequeue(&queue);
	Dequeue(&queue);

	Enqueue(&queue, 3);
	Enqueue(&queue, 1);
	Enqueue(&queue, 3);
	Enqueue(&queue, 1);

	printf("%d\n", Dequeue(&queue));

	return 0;
}