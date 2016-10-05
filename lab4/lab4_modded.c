/* Lab 4 Wrapper Program */

#include <stdio.h>
#include <math.h>

#define TRUE 1

double mag(double x,double y,double z);


int main(void) {
	int t;
	double  ax, ay, az; 	

	int minutes(int t);
	int seconds(int t);
	int millis(int t);

	while (TRUE) {
		scanf("%d,%lf,%lf,%lf", &t, &ax, &ay, &az);	

/* CODE SECTION 0 */
		printf("Echoing output: %8.3d, %7.4lf, %7.4lf, %7.4lf\n", t/1000, ax, ay, 
az);

/* 	CODE SECTION 1 */
		printf("At %d ms, the acceleration's magnitude was: %lf\n", t, mag(ax, ay, az));
/* 	CODE SECTION 2 */
		printf("At %d minutes, %d seconds, and %d milliseconds it was: %lf\n", minutes(t), seconds(t), millis(t), mag(ax,ay,az));

	}

return 0;
}

/* Put your functions here */

double mag(double x,double y,double z) {
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}

int minutes(int t) {
	return t / 1000 / 60;
}

int seconds(int t) {
	return t / 1000;
}

int millis(int t) {
	return t;
}