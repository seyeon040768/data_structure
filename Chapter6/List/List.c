#include <stdio.h>
#include <assert.h>

#define	MAX_LIST_SIZE 100

typedef struct
{
	int elements[MAX_LIST_SIZE];
	int size;
} List;

int IsFull(const List* list)
{
	return list->size == MAX_LIST_SIZE;
}

int IsEmpty(const List* list)
{
	return list->size == 0;
}

void Insert(List* list, int pos, int value)
{
	assert(!IsFull(list));
	assert(pos <= list->size);

	if (pos < 0)
	{
		pos = list->size;
	}

	for (int i = list->size; i > pos; --i)
	{
		list->elements[i] = list->elements[i - 1];
	}

	list->elements[pos] = value;
	++(list->size);
}

void Delete(List* list, int pos)
{
	if (pos < 0)
	{
		pos = list->size - 1;
	}

	if (pos >= list->size || pos < 0)
	{
		return;
	}

	for (int i = pos; i < list->size - 1; ++i)
	{
		list->elements[i] = list->elements[i + 1];
	}

	--(list->size);
}

void Clear(List* list)
{
	list->size = 0;
}

int GetValue(const List* list, int pos)
{
	if (pos < 0)
	{
		pos = list->size - 1;
	}

	assert(pos >= 0 && pos < list->size);

	return list->elements[pos];
}

int GetLength(const List* list)
{
	return list->size;
}

int main(void)
{
	List list = { .elements = { 0, }, .size = 0 };

	Insert(&list, 0, 1);
	Insert(&list, 0, 2);
	Insert(&list, 1, 3);
	Insert(&list, 0, 4);
	Insert(&list, -1, 1);

	Delete(&list, 0);
	Delete(&list, -1);
	Delete(&list, 2);

	printf("list[0]: %d\n", GetValue(&list, 0));
	printf("length: %d\n", GetLength(&list));

	Clear(&list);

	return 0;
}