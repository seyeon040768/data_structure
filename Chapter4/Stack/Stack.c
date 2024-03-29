#include <stdio.h>
#include <assert.h>

#define MAX_STACK_SIZE 100

typedef struct
{
	int elements[MAX_STACK_SIZE];
	int top;
} Stack;

int IsFull(const Stack* stack)
{
	return (stack->top == sizeof(stack->elements) - 1);
}

int IsEmpty(const Stack* stack)
{
	return (stack->top == -1);
}

void Push(Stack* stack, int value)
{
	assert(!IsFull(stack));

	++(stack->top);
	stack->elements[stack->top] = value;
}

int Pop(Stack* stack)
{
	assert(!IsEmpty(stack));

	return stack->elements[stack->top--];
}

int Peek(const Stack* stack)
{
	assert(!IsEmpty(stack));

	return stack->elements[stack->top];
}

int main(void)
{
	Stack stack = { .top = -1 };

	Push(&stack, 1);
	Push(&stack, 2);
	Push(&stack, 3);

	printf("%d\n", Pop(&stack)); // 3
	printf("%d\n", Peek(&stack)); // 2


	return 0;
}