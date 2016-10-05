#include <stdio.h>
#include <math.h>
#define PI 3.14159265359

/* 
Sean Hinchee
Section G
9/18/2015
*/

/*
All ints as whole numbers
All doubles to two decimal places
*/

int main() {
	int tmpi;
	double tmpd;
	
	/*** pre-determined equations ***/
	tmpi = 6427 + 1725;
	printf("a: %d\n", tmpi);
	
	tmpi = (6971 * 3925) - 95;
	printf("b: %d\n", tmpi);
	
	tmpd = 79 + 12 / 5;
	printf("c: %0.2lf\n", tmpd);
	
	tmpd = 3640 / 107.9;
	printf("d: %0.2lf\n", tmpd);
	
	tmpi = (22 / 3) * 3;
	printf("e: %d\n", tmpi);
	
	tmpi = 22 / (3 * 3);
	printf("f: %d\n", tmpi);
	
	tmpd = 22 / (3 * 3);
	printf("g: %0.2lf\n", tmpd);
	
	tmpd = 22 / 3 * 3;
	printf("h: %0.2lf\n", tmpd);
	
	tmpd = (22.0 / 3) * 3.0;
	printf("i: %0.2lf\n", tmpd);
	
	tmpi = 22.0 / (3 * 3.0);
	printf("j: %d\n", tmpi);
	
	tmpd = 22.0 / 3.0 * 3.0;
	printf("k: %0.2lf\n", tmpd);
	
	/*** custom equations ***/
	double r; // radius placeholder variable 
	
	/* C = 2*pi*r */
	r = 23.567 / (2.0 * PI);
	/* A = pi * r^2 */
	tmpd = PI * pow(r, 2.0);
	printf("l: %0.2lf\n", tmpd);
	
	/* m = (ft * 0.3048) */
	tmpd = 14.0 * 0.3048;
	printf("m: %0.2lf\n", tmpd);
	
	/* c = (f - 32)/1.8 */
	tmpd = (76.0 - 32.0) / 1.8;
	printf("n: %0.2lf\n", tmpd);
	
	
	return 0;
}