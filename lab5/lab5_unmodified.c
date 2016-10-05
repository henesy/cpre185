/* Lab 5 Wrapper Program */

#include <stdio.h>
#include <math.h>

#define TRUE 1

/* Put your lab 4 functions prototypes here, as well as the prototype for lab 5 */


int main(void) {
	int t, b1, b2, b3, b4, b5, s;
	double ax, ay, az; 	


	while (TRUE) {
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", &t, &ax, &ay, &az, &b1, &b2, &b3, &b4, &b5, &s );	

/* CODE SECTION 0 */
		printf("Echoing output: %d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d\n", t, ax, ay, az, b1, b2, b3, b4, b5, s);

/* 	CODE SECTION 1 
		printf("At %d ms, the acceleration's magnitude was: %f\n", t, mag(ax, ay, az));  
		
		You would be wise (mainly save time) if you copy your code to calculate the magnitude from last week
		 (lab 4) to this section.  You will also need to copy your prototypes and functions to the appropriate sections
		 in this program.   
		
		*/

		
		
	}


    return 0;
}

/* Put your lab 4 functions here, as well as your new function close_to */

