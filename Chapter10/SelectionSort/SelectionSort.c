#include <stdio.h>

void SelectionSort(int array[], int len)
{
	int temp, minIndex;
	for (int i = 0; i < len - 1; ++i)
	{
		minIndex = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (array[j] < array[minIndex])
			{
				minIndex = j;
			}
		}

		temp = array[i];
		array[i] = array[minIndex];
		array[minIndex] = temp;
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

	SelectionSort(array, sizeof(array) / sizeof(int));

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}