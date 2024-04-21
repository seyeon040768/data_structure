#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
	int data;
	struct Node* link;
} Node;

typedef struct
{
	Node* head;
	int length;
} CircularLinkedList;

int IsEmpty(const CircularLinkedList* list)
{
	return list->head == NULL;
}

Node* GetNode(const CircularLinkedList* list, const int pos)
{
	if (pos < 0 || pos >= list->length || IsEmpty(list))
	{
		return NULL;
	}

	Node* search = list->head->link;

	for (int i = 0; i < pos; ++i)
	{
		search = search->link;
	}

	return search;
}

int Insert(CircularLinkedList* list, const int pos, const int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return 0;
	}
	newNode->data = data;

	Node* prev = GetNode(list, pos - 1);

	if (pos == 0)
	{
		if (IsEmpty(list))
		{
			newNode->link = newNode;
			list->head = newNode;

			++(list->length);
			return 1;
		}
		
		prev = list->head;
	}
	else if (pos == list->length)
	{
		list->head = newNode;
	}

	if (prev == NULL)
	{
		free(newNode);
		return 0;
	}

	newNode->link = prev->link;
	prev->link = newNode;

	++(list->length);
	return 1;
}

void Delete(CircularLinkedList* list, const int pos)
{
	Node* prev = GetNode(list, pos - 1);

	if (pos == 0)
	{
		if (list->length == 1)
		{
			free(list->head);
			list->head = NULL;

			--(list->length);
			return;
		}
		prev = list->head;
	}
	else if (pos == list->length - 1)
	{
		list->head = prev;
	}

	if (prev == NULL || prev->link == NULL)
	{
		return;
	}

	Node* current = prev->link;
	prev->link = current->link;
	free(current);

	--(list->length);
}

void Clear(CircularLinkedList* list)
{
	if (IsEmpty(list))
	{
		return;
	}

	Node* search = list->head;
	Node* temp;

	do
	{
		temp = search->link;
		free(search);
		search = temp;
	} while (search != list->head);

	list->head = NULL;
	list->length = 0;
}

int GetLength(const CircularLinkedList* list)
{
	return list->length;
}

void PrintList(const CircularLinkedList* list)
{
	if (IsEmpty(list))
	{
		return;
	}

	Node* search = list->head;

	do
	{
		search = search->link;
		printf("%d ", search->data);
	} while (search != list->head);
	printf("\n");
}

int main(void)
{
	CircularLinkedList list = { .head = NULL, .length = 0 };

	printf("%d\n", Insert(&list, 1, 10)); // 0

	Insert(&list, 0, 1); // 1
	Insert(&list, 1, 2); // 1 2
	Insert(&list, 2, 3); // 1 2 3
	Insert(&list, 0, 4); // 4 1 2 3
	Insert(&list, 1, 5); // 4 5 1 2 3

	Delete(&list, 0); // 5 1 2 3
	Delete(&list, 2); // 5 1 3

	Clear(&list); // 

	return 0;
}