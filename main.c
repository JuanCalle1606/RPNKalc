#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define STACK 7
#define CMD(x) strcmp(input, (x)) == 0

typedef struct {
	double stack[STACK];
	int size;
} double_stack;

void printStack(double_stack *stack);

void printHelp(void);

int stackpop(double_stack *stack, double *out);

void stackpush(double_stack *stack, double d);

double radians(double a);

int main() {
	double_stack stack_v;
	stack_v.size = 0;
	double_stack *stack = &stack_v;
	char input[50];
	double a = 0, b = 0, mem = 0;

	while (1) {
		printf("mem: %lf\n", mem);
		printStack(stack);
		printf("> ");
		scanf("%s", input);
		printf("\033[2J");

		if (CMD("help")) {
			printHelp();
		} else if (CMD("exit")) {
			break;
		} else if (CMD("+")) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, a + b);
		} else if (CMD("-")) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, b - a);
		} else if (CMD("*")) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, a * b);
		} else if (CMD("/")) {
			if (stackpop(stack, &a) && stackpop(stack, &b)) {
				if (a) { stackpush(stack, b / a); }
				else { printf("Math Error: Division by 0\n"); }
			}
		} else if (CMD("pow")) {
			if (stackpop(stack, &a) && stackpop(stack, &b))
				stackpush(stack, pow(b, a));
		} else if (CMD("sqrt")) {
			if (stackpop(stack, &a)) {
				if (a >= 0) { stackpush(stack, sqrt(a)); }
				else { printf("Math Error: Sqrt of a negative value\n"); }
			}
		} else if (CMD("ln")) {
			if (stackpop(stack, &a)) {
				if (a > 0) { stackpush(stack, log(a)); }
				else { printf("Math Error: Logarithm of a negative value\n"); }
			}
		} else if (CMD("pi")) {
			stackpush(stack, M_PI);
		} else if (CMD("e")) {
			stackpush(stack, M_E);
		} else if (CMD("sin")) {
			if (stackpop(stack, &a))
				stackpush(stack, sin(radians(a)));
		} else if (CMD("cos")) {
			if (stackpop(stack, &a))
				stackpush(stack, cos(radians(a)));
		} else if (CMD("tan")) {
			if (stackpop(stack, &a)) {
				if (fmod(a, 90) == 0) { printf("Math Error: Tangent of a multiple of 90\n"); }
				else { stackpush(stack, tan(radians(a))); }
			}
		} else if (CMD("abs")) {
			if (stackpop(stack, &a))
				stackpush(stack, a < 0 ? a * -1 : a);
		} else if (CMD("exp")) {
			if (stackpop(stack, &a))
				stackpush(stack, exp(a));
		} else if (CMD("log")) {
			if (stackpop(stack, &a) && stackpop(stack, &b)) {
				if (a > 0 && b > 0) { stackpush(stack, log(b) / log(a)); }
				else { printf("Math Error: Logarithm of a negative value\n"); }
			}
		} else if (CMD("m+")) {
			if (stackpop(stack, &a)) {
				mem += a;
				stackpush(stack, a);
			}
		} else if (CMD("m-")) {
			if (stackpop(stack, &a)) {
				mem -= a;
				stackpush(stack, a);
			}
		} else if (CMD("mc")) {
			mem = 0;
		} else if (CMD("mr")) {
			stackpush(stack, mem);
		} else if (CMD("ms")) {
			if (stackpop(stack, &a)) {
				mem = a;
				stackpush(stack, a);
			}
		} else if (CMD("pop") || CMD("c")) {
			stackpop(stack, &a);
		} else if (CMD("clear") || CMD("ac")) {
			stack->size = 0;
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

inline double radians(double a) {
	return a * (M_PI / 180);
}

void stackpush(double_stack *stack, double d) {
	if (stack->size < STACK) {
		stack->stack[stack->size++] = d;
	} else {
		printf("Error: Not enough stack size to save.\n");
	}
}

void printHelp(void) {
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
	       "Memory and Stack:\n"
	       "m+: Add the value on first to the memory value, dont pop first\n"
	       "m-: Subtract the value on first from the memory value, dont pop first\n"
	       "mr: push the value in the memory onto the stack\n"
	       "mc: set the value of memory to 0\n"
	       "ms: set the value of memory to first, dont pop first\n"
	       "pop / c: remove the first element on the stack\n"
	       "clear / ac: clear all the stack\n\n"
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
