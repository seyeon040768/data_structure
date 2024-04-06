#include <stdio.h>
#include <assert.h>

#define MAX_QUEUE_SIZE 8

typedef struct
{
	int front;
	int rear;
	int elements[MAX_QUEUE_SIZE];
} Deque;

int IsFull(const Deque* queue)
{
	return (queue->front == (queue->rear + 1) % MAX_QUEUE_SIZE);
}

int IsEmpty(const Deque* queue)
{
	return (queue->front == queue->rear);
}

void AddRear(Deque* queue, int value)
{
	assert(!IsFull(queue));

	queue->rear = (queue->rear + 1) % MAX_QUEUE_SIZE;
	queue->elements[queue->rear] = value;
}

int DeleteRear(Deque* queue)
{
	assert(!IsEmpty(queue));

	int ret = queue->elements[queue->rear];

	queue->rear = (queue->rear - 1) % MAX_QUEUE_SIZE;

	return ret;
}

void AddFront(Deque* queue, int value)
{
	assert(!IsFull(queue));

	queue->elements[queue->front] = value;
	queue->front = (queue->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

int DeleteFront(Deque* queue)
{
	assert(!IsEmpty(queue));

	queue->front = (queue->front + 1) % MAX_QUEUE_SIZE;
	return queue->elements[queue->front];
}

int GetRear(Deque* queue)
{
	assert(!IsEmpty(queue));

	return queue->elements[queue->rear];
}

int GetFront(Deque* queue)
{
	assert(!IsEmpty(queue));

	return queue->elements[(queue->front + 1) % MAX_QUEUE_SIZE];
}

int main(void)
{
	Deque queue = { .front = 0, .rear = 0 };

	AddRear(&queue, 1);
	AddRear(&queue, 2);
	AddRear(&queue, 3);
	AddFront(&queue, 4);
	AddFront(&queue, 5);
	AddFront(&queue, 6);
	AddFront(&queue, 7);
	//Enqueue(&queue, 1);

	DeleteRear(&queue);
	DeleteRear(&queue);
	DeleteFront(&queue);
	DeleteFront(&queue);

	printf("%d\n", GetRear(&queue));

	return 0;
}