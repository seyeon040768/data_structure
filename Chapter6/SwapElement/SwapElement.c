#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_COUNT 20
#define STOP_INPUT_LIST_FLAG -1
#define STOP_INPUT_POS_FLAG 'q'

typedef int element;
typedef struct DListNode
{
	element data;
	struct DListNode* lLink;
	struct DListNode* rLink;
} DListNode;

void Init(DListNode* head)
{
	head->lLink = head;
	head->rLink = head;
}

void PrintList(DListNode* head)
{
	DListNode* search = head->rLink;
	while (search->rLink != head)
	{
		printf("%d > ", search->data);
		search = search->rLink;
	}
	printf("%d\n", search->data);
}

void DInsert(DListNode* before, element data, DListNode* newNode)
{
	if (newNode == NULL)
	{
		newNode = (DListNode*)malloc(sizeof(DListNode));
		newNode->data = data;
	}
	newNode->lLink = before;
	newNode->rLink = before->rLink;
	before->rLink->lLink = newNode;
	before->rLink = newNode;
}

void DDelete(DListNode* head, DListNode* removed, int freeNode)
{
	if (removed == head)
	{
		return;
	}
	removed->lLink->rLink = removed->rLink;
	removed->rLink->lLink = removed->lLink;

	if (freeNode)
	{
		free(removed);
	}
}

void DSwap(DListNode* head, int pos1, int pos2)
{
	if (pos1 > pos2)
	{
		int temp = pos1;
		pos1 = pos2;
		pos2 = temp;
	}

	DListNode* firstNode = head->rLink;
	DListNode* secondNode = NULL;
	DListNode* firstBefore = NULL;


	for (int i = 0; i < pos1; ++i)
	{
		firstNode = firstNode->rLink;
	}

	firstBefore = firstNode->lLink;
	secondNode = firstNode;

	for (int i = 0; i < pos2 - pos1; ++i)
	{
		secondNode = secondNode->rLink;
	}

	DDelete(head, firstNode, 0);
	DInsert(secondNode, 0, firstNode);

	DDelete(head, secondNode, 0);
	DInsert(firstBefore, 0, secondNode);
}

void InputError()
{
	printf("Error: �߸��� �Է��� �ֽ��ϴ�. �ڿ����� �Է��� �ּ���.\n");
	while (getchar() != '\n');
}

int main(void)
{
	int inputBuffer[MAX_INPUT_COUNT] = { 0 };
	int length = 0;
	int isInputSucceed = 0;
	int pos1 = 0, pos2 = 0;
	char stringBuffer[10];
	char* stop = NULL;

	DListNode* head = (DListNode*)malloc(sizeof(DListNode));
	Init(head);

	while (!isInputSucceed)
	{
		printf("�ڿ��� ����Ʈ �Է�(�ִ� %d�� %d�� ����): ", MAX_INPUT_COUNT, STOP_INPUT_LIST_FLAG);
		for (int i = 0; i < MAX_INPUT_COUNT; ++i)
		{
			element temp;
			if (scanf("%d", &temp) != 1) // �Է��� �߸��� ���
			{
				InputError();
				break;
			}

			if (temp == STOP_INPUT_LIST_FLAG)
			{
				length = i;
				isInputSucceed = 1;
				break;
			}
			else if (temp <= 0)
			{
				InputError();
				break;
			}
			else
			{
				inputBuffer[i] = temp;
			}
		}
	}

	for (int i = 0; i < length; ++i)
	{
		DInsert(head, inputBuffer[i], NULL);
	}
	printf("�Է� ���: ");
	PrintList(head);

	while (getchar() != '\n');

	while (1)
	{
		printf("��ġ ���� (����: �ε���1 �ε���2, ����: %c): ", STOP_INPUT_POS_FLAG);
		fgets(stringBuffer, 10, stdin);
		if (stringBuffer[0] == STOP_INPUT_POS_FLAG)
		{
			break;
		}

		pos1 = strtol(stringBuffer, &stop, 10);
		pos2 = strtol(stop, &stop, 10);

		if (pos1 < 0 || pos1 >= length || pos2 < 0 || pos2 >= length)
		{
			printf("Error: The specified index is out of range. Please enter a valid index.\n");
		}
		else
		{
			DSwap(head, pos1, pos2);
		}

		PrintList(head);
	}

	printf("���� ���: ");
	PrintList(head);

	for (int i = 0; i < length; ++i)
	{
		DDelete(head, head->rLink, 1);
	}
	free(head);

	return 0;
}