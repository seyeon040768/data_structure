#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct Node
{
	int data;
	struct Node* lLink;
	struct Node* rLink;
} Node;

typedef struct
{
	Node* head;
	int length;
} DoublyLinkedList;

int IsEmpty(const DoublyLinkedList* list)
{
	return list->head == NULL;
}

Node* GetNode(const DoublyLinkedList* list, const int pos)
{
	if (pos < 0 || pos >= list->length || IsEmpty(list))
	{
		return NULL;
	}

	Node* search = list->head;
	for (int i = 0; i < pos; ++i)
	{
		search = search->rLink;
	}

	return search;
}

int Insert(DoublyLinkedList* list, const int pos, const int data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		return 0;
	}
	newNode->data = data;

	if (pos == 0)
	{
		newNode->rLink = list->head;
		if (list->head != NULL)
		{
			list->head->lLink = newNode;
		}
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

	if (prev->rLink != NULL)
	{
		prev->rLink->lLink = newNode;
	}
	newNode->rLink = prev->rLink;
	newNode->lLink = prev;
	prev->rLink = newNode;

	++(list->length);
	return 1;
}

void Delete(DoublyLinkedList* list, const int pos)
{
	if (pos == 0)
	{
		Node* current = list->head;
		list->head = current->rLink;
		if (list->head != NULL)
		{
			list->head->lLink = NULL;
		}
		free(current);

		--(list->length);
		return;
	}

	Node* prev = GetNode(list, pos - 1);
	if (prev == NULL || prev->rLink == NULL)
	{
		return;
	}

	Node* current = prev->rLink;
	prev->rLink = current->rLink;
	current->rLink->lLink = prev;
	free(current);

	--(list->length);
}

void Clear(DoublyLinkedList* list)
{
	Node* search = list->head;
	Node* temp;

	while (search != NULL)
	{
		temp = search->rLink;
		free(search);
		search = temp;
	}

	list->head = NULL;
	list->length = 0;
}

int GetLength(const DoublyLinkedList* list)
{
	return list->length;
}

void PrintList(const DoublyLinkedList* list)
{
	Node* search = list->head;

	while (search != NULL)
	{
		printf("%d ", search->data);
		search = search->rLink;
	}

	printf("\n");
}

int main(void)
{
	DoublyLinkedList list = { .head = NULL, .length = 0 };

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