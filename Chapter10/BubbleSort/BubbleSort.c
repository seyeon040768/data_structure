#include <stdio.h>

void BubbleSort(int array[], int len)
{
	int temp;
	for (int i = len - 1; i > 0; --i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (array[j] > array[j + 1])
			{
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
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

	BubbleSort(array, sizeof(array) / sizeof(int));

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}