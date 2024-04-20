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
} SinglyLinkedList;

int IsEmpty(const SinglyLinkedList* list)
{
	return list->head == NULL;
}

Node* GetNode(const SinglyLinkedList* list, const int pos)
{
	if (pos < 0 || pos >= list->length)
	{
		return NULL;
	}

	Node* search = list->head;

	for (int i = 0; i < pos; ++i)
	{
		search = search->link;
	}

	return search;
}

int Insert(SinglyLinkedList* list, const int pos, const int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return 0;
	}
	newNode->data = data;

	if (pos == 0)
	{
		newNode->link = list->head;
		list->head = newNode;

		++(list->length);
		return 1;
	}

	Node* prev;
	if ((prev = GetNode(list, pos - 1)) == NULL)
	{
		free(newNode);
		return 0;
	}

	newNode->link = prev->link;
	prev->link = newNode;
	
	++(list->length);
	return 1;
}

void Delete(SinglyLinkedList* list, const int pos)
{
	if (pos == 0)
	{
		Node* current = list->head;
		list->head = current->link;
		free(current);

		--(list->length);
		return;
	}

	Node* prev = GetNode(list, pos - 1);
	if (prev == NULL || prev->link == NULL)
	{
		return;
	}

	Node* current = prev->link;
	prev->link = current->link;
	free(current);

	--(list->length);
}

void Clear(SinglyLinkedList* list)
{
	Node* search = list->head;
	Node* temp;

	while (search != NULL)
	{
		temp = search->link;
		free(search);
		search = temp;
	}

	list->length = 0;
}

int GetLength(const SinglyLinkedList* list)
{
	return list->length;
}

void PrintList(const SinglyLinkedList* list)
{
	Node* search = list->head;

	while (search != NULL)
	{
		printf("%d ", search->data);

		search = search->link;
	}
	printf("\n");
}

void Reverse(SinglyLinkedList* list)
{
	Node* current = list->head;
	Node* prev = NULL;
	Node* next;

	while (current != NULL)
	{
		next = current->link;
		current->link = prev;
		prev = current;
		current = next;
	}

	list->head = prev;
}

int main(void)
{
	SinglyLinkedList list = { .head = NULL, .length = 0 };

	printf("%d\n", Insert(&list, 1, 10)); // 0

	Insert(&list, 0, 1); // 1
	Insert(&list, 1, 2); // 1 2
	Insert(&list, 2, 3); // 1 2 3
	Insert(&list, 0, 4); // 4 1 2 3
	Insert(&list, 1, 5); // 4 5 1 2 3

	Reverse(&list); // 3 2 1 5 4

	Delete(&list, 0); // 2 1 5 4
	Delete(&list, 2); // 2 1 4

	Clear(&list); // 

	return 0;
}