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

int ConvertInfixToPostfix(char* expression, char* result)
{
	if (!CheckParanthesis(expression))
	{
		return 0;
	}

	Stack operatorStack = { .top = -1 };
	char topOperator;

	while (*expression != '\0')
	{
		switch (*expression)
		{
		case '*':
		case '/':
		case '(':
			Push(&operatorStack, *expression);
			break;
		case '+':
		case '-':
			if (!IsEmpty(&operatorStack))
			{
				topOperator = Peek(&operatorStack);
				if (topOperator == '*' || topOperator == '/')
				{
					*result = Pop(&operatorStack);
					++result;
				}
			}
			Push(&operatorStack, *expression);
			break;
		case ')':
			while ((topOperator = Pop(&operatorStack)) != '(')
			{
				*result = topOperator;
				++result;
			}
				break;
		default:
			*result = *expression;
			++result;
			break;
		}

		++expression;
	}

	while (!IsEmpty(&operatorStack))
	{
		*result = Pop(&operatorStack);
		++result;
	}

	*result = '\0';

	return 1;
}

int EvaluatePostfix(char* expression)
{
	Stack stack = { .top = -1 };
	int firstNum, secondNum, temp;

	while (*expression != '\0')
	{
		switch (*expression)
		{
		case '*':
			secondNum = Pop(&stack);
			firstNum = Pop(&stack);
			temp = firstNum * secondNum;
			Push(&stack, temp);
			break;
		case '/':
			secondNum = Pop(&stack);
			firstNum = Pop(&stack);
			temp = firstNum / secondNum;
			Push(&stack, temp);
			break;
		case '+':
			secondNum = Pop(&stack);
			firstNum = Pop(&stack);
			temp = firstNum + secondNum;
			Push(&stack, temp);
			break;
		case '-':
			secondNum = Pop(&stack);
			firstNum = Pop(&stack);
			temp = firstNum - secondNum;
			Push(&stack, temp);
			break;
		default:
			Push(&stack, *expression - '0');
			break;
		}

		++expression;
	}

	return Pop(&stack);
}

int main(void)
{
	char expression[] = "(2+3)*4+9";
	char postfixExpression[100] = { '\0' };
	int result;

	ConvertInfixToPostfix(expression, postfixExpression);
	result = EvaluatePostfix(postfixExpression);

	printf("expression: %s\n", expression); // expression: (2+3)*4+9
	printf("postfix: %s\n", postfixExpression); // postfix: 23+4*9+
	printf("eval: %d\n", result); // eval: 29

	return 0;
}