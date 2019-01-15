#include <stdio.h>

/*	@Doc
	This program demostrates passing functions as function arguements by passing
	the address of the function directly.
*/

int add(int a, int b) {
	return a + b;
}

int execute(int f(int a, int b), int a, int b) {
	return f(a, b);
}

void main (void) {
	printf("%d", execute(add, 10, 6));
}