#include <stdio.h>
#include <stdlib.h>

void MergeRecursive(int array[], int temp[], int left, int right)
{
	if (left == right)
	{
		return;
	}
	int mid = (left + right) / 2;
	int i, j, k;

	MergeRecursive(array, temp, left, mid);
	MergeRecursive(array, temp, mid + 1, right);

	i = left;
	j = mid + 1;
	k = left;
	while (i <= mid && j <= right)
	{
		if (array[i] <= array[j])
		{
			temp[k++] = array[i++];
		}
		else
		{
			temp[k++] = array[j++];
		}
	}

	while (i <= mid)
	{
		temp[k++] = array[i++];
	}

	while (j <= right)
	{
		temp[k++] = array[j++];
	}

	for (i = left; i <= right; ++i)
	{
		array[i] = temp[i];
	}
}

void MergeSort(int array[], int left, int right)
{
	int* temp = (int*)malloc(sizeof(int) * (right - left + 1));

	MergeRecursive(array, temp, left, right);

	free(temp);
}

int main(void)
{
	int array[10] = { 4, 2, 6, 1, 9, 3, 0, 8, 7, 5 };

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	MergeSort(array, 0, sizeof(array) / sizeof(int) - 1);

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}