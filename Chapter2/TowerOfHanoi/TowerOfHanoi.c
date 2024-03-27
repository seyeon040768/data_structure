#include <stdio.h>

void PrintMovingDisc(int discNum, char source, char destination)
{
	printf("%d: %c -> %c\n", discNum, source, destination);
}

void TowerOfHanoiRecursive(int countDisc, char start, char temp, char end)
{
	if (countDisc == 1)
	{
		PrintMovingDisc(countDisc, start, end);

		return;
	}

	TowerOfHanoiRecursive(countDisc - 1, start, end, temp);
	PrintMovingDisc(countDisc, start, end);
	TowerOfHanoiRecursive(countDisc - 1, temp, start, end);
}

int main(void)
{
	int countDisc = 4;

	TowerOfHanoiRecursive(countDisc, 'A', 'B', 'C');

	return 0;
}