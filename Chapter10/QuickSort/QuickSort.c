#include <stdio.h>
#include <stdlib.h>

void QuickSort(int array[], int left, int right)
{
    if (left >= right)
    {
        return;
    }

    int pivot = array[left];
    int low = left + 1;
    int high = right;
    int temp;

    while (low <= high)
    {
        while (low <= high && array[low] <= pivot)
        {
            ++low;
        }

        while (low <= high && array[high] >= pivot)
        {
            --high;
        }

        if (low < high)
        {
            temp = array[low];
            array[low] = array[high];
            array[high] = temp;
        }
    }

    array[left] = array[high];
    array[high] = pivot;

    QuickSort(array, left, high - 1);
    QuickSort(array, high + 1, right);
}

int main(void)
{
	int array[10] = { 4, 2, 6, 1, 9, 3, 0, 8, 7, 5 };

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	QuickSort(array, 0, sizeof(array) / sizeof(int) - 1);

	for (int i = 0; i < 10; ++i)
	{
		printf("%d ", array[i]);
	}
	printf("\n");

	return 0;
}