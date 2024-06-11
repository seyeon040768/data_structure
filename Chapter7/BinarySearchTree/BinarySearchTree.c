#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
	int data;
	struct TreeNode* left;
	struct TreeNode* right;
} TreeNode;

TreeNode* MakeNode(int key)
{
	TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		exit(1);
	}
	node->data = key;
	node->left = NULL;
	node->right = NULL;

	return node;
}

TreeNode* Search(TreeNode* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->data == key)
	{
		return node;
	}

	if (node->data > key)
	{
		Search(node->left, key);
	}
	else
	{
		Search(node->right, key);
	}
}

TreeNode* Insert(TreeNode* node, int key)
{
	if (node == NULL)
	{
		return MakeNode(key);
	}

	if (node->data > key)
	{
		node->left = Insert(node->left, key);
	}
	else
	{
		node->right = Insert(node->right, key);
	}

	return node;
}

TreeNode* Delete(TreeNode* node, int key)
{
	if (node == NULL)
	{
		return NULL;
	}

	if (node->data > key)
	{
		node->left = Delete(node->left, key);
	}
	else if (node->data < key)
	{
		node->right = Delete(node->right, key);
	}
	else
	{
		if (node->left == NULL) // case 1 or 2
		{
			TreeNode* temp = node->right;
			free(node);
			return temp;
		}
		else if (node->right == NULL) // case 1
		{
			TreeNode* temp = node->left;
			free(node);
			return temp;
		}

		// case 3
		TreeNode* leftMax = node->left;
		while (leftMax->right != NULL)
		{
			leftMax = leftMax->right;
		}

		TreeNode* rightMin = node->right;
		while (rightMin->left != NULL)
		{
			rightMin = rightMin->left;
		}

		return leftMax; // or rightMin
	}
}

int main(void)
{
	TreeNode* root = Insert(NULL, 5);
	Insert(root, 3);
	Insert(root, 4);
	Insert(root, 7);
	Insert(root, 9);
	Insert(root, 1);
	Insert(root, 0);
	Insert(root, 11);
	Insert(root, 2);

	Delete(root, 1);

	return 0;
}