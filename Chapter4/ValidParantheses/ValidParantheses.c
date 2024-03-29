#include <stdio.h>
#include <string.h>
#include <assert.h>

#define MAX_STACK_SIZE 100

typedef struct
{
	char elements[MAX_STACK_SIZE];
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

void Push(Stack* stack, char value)
{
	assert(!IsFull(stack));

	++(stack->top);
	stack->elements[stack->top] = value;
}

char Pop(Stack* stack)
{
	assert(!IsEmpty(stack));

	return stack->elements[stack->top--];
}

int CheckParanthesis(char* str, int len)
{
	Stack paranthesisStack = { .top = -1 };

	for (int i = 0; i < len; ++i)
	{
		switch (*(str + i))
		{
		case '[':
		case '{':
		case '(':
			Push(&paranthesisStack, *(str + i));
			break;

		case ']':
			if (IsEmpty(&paranthesisStack) || Pop(&paranthesisStack) != '[')
			{
				return 0;
			}
			break;
		case '}':
			if (IsEmpty(&paranthesisStack) || Pop(&paranthesisStack) != '{')
			{
				return 0;
			}
			break;
		case ')':
			if (IsEmpty(&paranthesisStack) || Pop(&paranthesisStack) != '(')
			{
				return 0;
			}
			break;
		}
	}

	return 1;
}

int main(void)
{
	char valid[] = "{arr[Func(a)-(i + j)]}";
	char invalid[] = "}{a(i + 1)[][](}";

	printf("valid: %d\n", CheckParanthesis(valid, strlen(valid))); // valid: 1
	printf("invalid: %d\n", CheckParanthesis(invalid, strlen(invalid))); // invalid: 0


	return 0;
}