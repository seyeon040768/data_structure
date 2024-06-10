#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

void Preorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	printf("%d\n", node->data);
	Preorder(node->left);
	Preorder(node->right);
}

void Inorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	Inorder(node->left);
	printf("%d\n", node->data);
	Inorder(node->right);
}

void Postorder(TreeNode* node)
{
	if (node == NULL)
	{
		return;
	}

	Postorder(node->left);
	Postorder(node->right);
	printf("%d\n", node->data);
}


#define MAX_QUEUE_SIZE 100

typedef struct
{
	int front;
	int rear;
	TreeNode* elements[MAX_QUEUE_SIZE];
} Queue;

int IsFull(const Queue* queue)
{
	return (queue->rear == MAX_QUEUE_SIZE - 1);
}

int IsEmpty(const Queue* queue)
{
	return (queue->front == queue->rear);
}

void Enqueue(Queue* queue, TreeNode* value)
{
	queue->elements[++(queue->rear)] = value;
}

TreeNode* Dequeue(Queue* queue)
{
	return queue->elements[++(queue->front)];
}

void Levelorder(TreeNode* root)
{
	Queue queue = { .front = -1, .rear = -1 };

	Enqueue(&queue, root);
	while (!IsEmpty(&queue))
	{
		TreeNode* node = Dequeue(&queue);
		printf("%d\n", node->data);
		if (node->left != NULL)
		{
			Enqueue(&queue, node->left);
		}
		if (node->right != NULL)
		{
			Enqueue(&queue, node->right);
		}
	}
}

int main(void)
{


	return 0;
}