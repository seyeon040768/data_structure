#include <stdio.h>

void InsertionSort(int array[], int len)
{
	int i, j, key;

	for (i = 1; i < len; ++i)
	{
		key = array[i];
		for (j = i - 1; j >= 0; --j)
		{
			if (array[j] > key)
			{
				array[j + 1] = array[j];
			}
			else
			{
				break;
			}
		}
		array[j + 1] = key;
	}
}

int main(void)
{
	int array[10] = { 4, 2, 6, 1, 9, 3, 0, 8, 7, 5 };

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	InsertionSort(array, sizeof(array) / sizeof(int));

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}