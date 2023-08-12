#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define STACK 7

typedef struct {
	double stack[STACK];
	int size;
} double_stack;

void printStack(double_stack *stack);

void printHelp();

int stackpop(double_stack *stack, double *out);

void stackpush(double_stack *stack, double d);

int main() {
	double_stack stack_v;
	stack_v.size = 0;
	double_stack *stack = &stack_v;
	char input[50];
	double a = 0, b = 0;

	while (1) {
		printStack(stack);
		printf("> ");
		scanf("%s", input);

		if (strcmp(input, "help") == 0) {
			printHelp();
		} else if (strcmp(input, "exit") == 0) {
			break;
		} else if (strcmp(input, "+") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, a + b);
		} else if (strcmp(input, "-") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, b - a);
		} else if (strcmp(input, "*") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, a * b);
		} else if (strcmp(input, "/") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, b / a);
		} else if (strcmp(input, "pow") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, pow(b, a));
		} else if (strcmp(input, "sqrt") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, sqrt(a));
		} else if (strcmp(input, "ln") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, log(a));
		} else if (strcmp(input, "pi") == 0) {
			stackpush(stack, M_PI);
		} else if (strcmp(input, "e") == 0) {
			stackpush(stack, M_E);
		} else if (strcmp(input, "sin") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, sin(a));
		} else if (strcmp(input, "cos") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, cos(a));
		} else if (strcmp(input, "tan") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, tan(a));
		} else if (strcmp(input, "abs") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, a < 0 ? a * -1 : a);
		} else if (strcmp(input, "exp") == 0) {
			if (stackpop(stack, &a))
				stackpush(stack, exp(a));
		} else if (strcmp(input, "log") == 0) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, log(b) / log(a));
		} else {
			// try to read number
			char *tmp;
			double val = strtod(input, &tmp);
			if (tmp == input) {
				printf("Error: Invalid input or command.\n");
			} else {
				stackpush(stack, val);
			}
		}
	}

	return 0;
}

void stackpush(double_stack *stack, double d) {
	if (stack->size < STACK) {
		stack->stack[stack->size++] = d;
	} else {
		printf("Error: Not enough stack size to save.\n");
	}
}

void printHelp() {
	printf("Commands: \n"
	       "help: show this help\n"
	       "exit: close the app\n\n"
	       "Basic operations:\n"
	       "+: add first and second\n"
	       "-: subtracts second with first\n"
	       "*: multiply first and second\n"
	       "/: divide second by first\n"
	       "abs: absolute value of first\n\n"
	       "Power functions:\n"
	       "pow: raise second to first\n"
	       "sqrt: compute square root of first\n\n"
	       "Trigonometric functions:\n"
	       "sin: compute cosine of first\n"
	       "cos: compute sine of first\n"
	       "tan: compute tangent of first\n\n"
	       "Exponential and logarithmic functions:\n"
	       "ln: Compute natural logarithm of first\n"
	       "exp: Compute exponential function, which is e raised to the power first\n"
	       "log: Compute the logarithm of second with base in first\n\n"
	       "Constants:\n"
	       "pi: push pi value\n"
	       "e: push e value\n\n"
	       "Press enter to continue\n"
	);
	char tmp;
	getchar();
	scanf("%c", &tmp);
}

void printStack(double_stack *stack) {
	for (int i = 0; i < STACK; ++i) {
		if (i < STACK - stack->size) {
			printf("%i: \n", STACK - i);
		} else {
			printf("%i: %lf\n", STACK - i, stack->stack[stack->size - (STACK - i)]);
		}
	}
}

int stackpop(double_stack *stack, double *out) {
	if (stack->size) {
		*out = stack->stack[--stack->size];
		return 1;
	}
	printf("Error: Not enough operands.\n");
	return 0;
}
