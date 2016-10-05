// LAB2-0.c : Defines the entry point for the console application.

#include <stdio.h>

int main(int argc, char* argv[]) {
	int x, y;
	printf("Enter a width: ");
	scanf("%d", &x);
	printf("Enter a height: ");
	scanf("%d", &y);
	printf("A %d by %d rectangle's area is %d\n", x, y, x*y);
	return 0;
}

