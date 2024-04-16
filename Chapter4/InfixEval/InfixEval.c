#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_INFIX_LEN 101
#define MAX_STACK_SIZE 100

typedef int element;

typedef struct
{
	element elements[MAX_STACK_SIZE];
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

void Push(Stack* stack, element value)
{
	if (IsFull(stack))
	{
		printf("stack is full!");
		exit(1);
	}

	++(stack->top);
	stack->elements[stack->top] = value;
}

element Pop(Stack* stack)
{
	if (IsEmpty(stack))
	{
		printf("stack is empty!");
		exit(1);
	}

	return stack->elements[stack->top--];
}

element Peek(const Stack* stack)
{
	if (IsEmpty(stack))
	{
		printf("stack is empty!");
		exit(1);
	}

	return stack->elements[stack->top];
}


element infix2StackEval(char* infix)
{
	Stack numStack = { .top = -1 };
	Stack operatorStack = { .top = -1 };

	while (*infix != '\0')
	{
		if (*infix == ')')
		{
			element b = Pop(&numStack);
			element a = Pop(&numStack);

			switch (Pop(&operatorStack))
			{
			case '+':
				Push(&numStack, a + b);
				break;
			case '-':
				Push(&numStack, a - b);
				break;
			case '*':
				Push(&numStack, a * b);
				break;
			case '/':
				Push(&numStack, a / b);
				break;
			}
		}
		else if (*infix >= '0' && *infix <= '9')
		{
			element temp = (element)(*infix - '0');

			while (*(infix + 1) >= '0' && *(infix + 1) <= '9')
			{
				++infix;

				temp *= 10;
				temp += (element)(*infix - '0');
			}

			Push(&numStack, temp);
		}
		else if (*infix == '+' || *infix == '-' || *infix == '*' || *infix == '/')
		{
			Push(&operatorStack, *infix);
		}
		++infix;
	}

	return Pop(&numStack);
}

int main(void)
{
	char infix[MAX_INFIX_LEN] = { '\0', };
	scanf("%[^\n]s", infix);

	printf("%d\n", infix2StackEval(infix));

	return 0;
}

