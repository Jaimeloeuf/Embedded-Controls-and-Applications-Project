#include <stdio.h>

/*	@Doc
	This program demostrates the use of file pointer together with typedef keyword.
*/

typedef int (*fp)(int a, int b);

int add(int a, int b) {
	return a + b;
}

fp func = &add;

void main (void) {
	printf("%d", func(5, 6));
}