#include <stdio.h>

int FactorialRecursive(int n)
{
	if (n == 1)
	{
		return 1;
	}

	return n * FactorialRecursive(n - 1);
}

int main(void)
{
	int n = 5;

	printf("%d\n", FactorialRecursive(n));

	return 0;
}