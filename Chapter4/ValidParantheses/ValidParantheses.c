#include <stdio.h>
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

int CheckParanthesis(char* str)
{
	Stack paranthesisStack = { .top = -1 };

	while (*str != '\0')
	{
		switch (*str)
		{
		case '[':
		case '{':
		case '(':
			Push(&paranthesisStack, *str);
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

		++str;
	}

	return 1;
}

int main(void)
{
	char valid[] = "{arr[Func(a)-(i + j)]}";
	char invalid[] = "{a(i + 1)[][](}";

	printf("valid: %d\n", CheckParanthesis(valid)); // valid: 1
	printf("invalid: %d\n", CheckParanthesis(invalid)); // invalid: 0


	return 0;
}