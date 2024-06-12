#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 200

typedef struct
{
	int heap[MAX_HEAP_SIZE];
	int heapSize;
} Heap;

Heap* Create()
{
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	if (heap == NULL)
	{
		exit(1);
	}
	heap->heapSize = 0;

	return heap;
}

int IsEmpty(Heap* heap)
{
	return heap->heapSize == 0;
}

int IsFull(Heap* heap)
{
	return heap->heapSize == MAX_HEAP_SIZE - 1;
}

void Insert(Heap* heap, int key)
{
	if (IsFull(heap))
	{
		return;
	}

	int i = ++(heap->heapSize);

	while ((i != 1) && (key > heap->heap[i / 2]))
	{
		heap->heap[i] = heap->heap[i / 2];
		i /= 2;
	}

	heap->heap[i] = key;
}

int Delete(Heap* heap)
{
	if (IsEmpty(heap))
	{
		return -1;
	}

	int ret = heap->heap[1];
	int last = heap->heap[(heap->heapSize)--];
	int i = 1;
	int next = i * 2;

	while (next <= heap->heapSize)
	{
		if ((next < heap->heapSize) && (heap->heap[next] < heap->heap[next + 1]))
		{
			++next;
		}

		if (last >= heap->heap[next])
		{
			break;
		}

		heap->heap[i] = heap->heap[next];
		i = next;
		next = i * 2;
	}

	heap->heap[i] = last;

	return ret;
}

int main(void)
{

	return;
}