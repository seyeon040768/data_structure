#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
	int isThread;
} TreeNode;

TreeNode* FindSuccessor(TreeNode* node)
{
	TreeNode* ret = node->right;
	if (ret == NULL || ret->isThread)
	{
		return ret;
	}

	while (ret->left != NULL)
	{
		ret = ret->left
	}

	return ret;
}

void Inorder(TreeNode* root)
{
	TreeNode* node = root;
	
	while (node->left != NULL)
	{
		node = node->left;
	}

	do
	{
		printf("%d\n", node->data);
		node = FindSuccessor(node);
	} while (node != NULL);
}