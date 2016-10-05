/* Lab 5 Wrapper Program */

#include <stdio.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define FRONT 6
#define BACK 7

int numButtons(int b[6]);
double mag(double x,double y,double z);
int close_to(double tolerance, double point, double value);

int main(void) {
	/* b2 is the "UP" button */
	int t, b1, b2, b3, b4, b5, s, printed;
	double ax, ay, az, ox, oy, oz; 	

	b2 = 0;
	printed = FALSE;
	ox = ax, oy = ay, oz = az;
	while (b2 < 1) {
		if(printed == FALSE) {
			ox = ax, oy = ay, oz = az;
		}
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", &t, &ax, &ay, &az, &b1, &b2, &b3, &b4, &b5, &s );	

/* CODE SECTION 0 */
		//printf("Echoing output: %d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d\n", t, ax, ay, az, b1, b2, b3, b4, b5, s);

/* 	CODE SECTION 1 */
		//printf("At %d ms, the acceleration's magnitude was: %f\n", t, mag(ax, ay, az));  
		/*
			UP: z > x && z > y
			DOWN: x > y && x > z
			LEFT: x > y && z < y
			RIGHT: x < y && z < y
			FRONT: y < 1 && z < 0
			BACK: x < 0 && y < 0 && z < 0
			
			UP: x:0 y:0 z: 1
			DOWN: x:0 y:0 z:-1
			LEFT: x:1 y:0 z>0 
			RIGHT: x:-1 y:0 z>0 
			FRONT: x:0 y:1 z:0
			BACK: x:0 y:-1 z:0 
		*/
		/* close_to(tol, pt, val) */
		
		if(close_to(0.01, 1, az) == TRUE) {
			if(printed != UP && close_to(0.01, 1, mag(ax, ay, az))){
				printf("UP!\n");
				printed=UP;
			}
			ox = ax, oy = ay, oz = az;
		} else if (close_to(0.01, -1, az) == TRUE) {
			if(printed != DOWN && close_to(0.01, 1, mag(ax, ay, az)) ){
				printf("DOWN!\n");
				printed=DOWN;
			}
			ox = ax, oy = ay, oz = az;
		} else if (close_to(0.01, 1, ax) == TRUE) {
			if(printed != LEFT && close_to(0.01, 1, mag(ax, ay, az))) {
				printf("LEFT!\n");
				printed=LEFT;
			}
			ox = ax, oy = ay, oz = az;
		} else if (close_to(0.01, -1, ax) == TRUE) {
			if(printed != RIGHT && close_to(0.01, 1, mag(ax, ay, az))){
				printf("RIGHT!\n");
				printed=RIGHT;
			}
			ox = ax, oy = ay, oz = az;
		} else if (close_to(0.01, 1, ay) == TRUE) {
			if(printed != FRONT && close_to(0.01, 1, mag(ax, ay, az))) {
				printf("FRONT!\n");
				printed=FRONT;
			}
			ox = ax, oy = ay, oz = az;
			
		} else if (close_to(0.01, -1, ay) == TRUE) {
			if(printed != BACK && close_to(0.01, 1, mag(ax, ay, az)))  {
				printf("BACK!\n");
				printed=BACK;
			}
			ox = ax, oy = ay, oz = az;
		}
		
		/*
		if(ay < 1 && az < 0) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("FRONT!\n");
			}
			ox = ax, oy = ay, oz = az;
		} else if(ax < ay && ax > az) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("DOWN!\n");
			}
			ox = ax, oy = ay, oz = az;
		} else if(ax > ay && az < ay) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("LEFT!\n");
			}
			ox = ax, oy = ay, oz = az;
		} else if(ax < ay && az < ay) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("RIGHT!\n");
			}
			ox = ax, oy = ay, oz = az;
		} else if(az > ax && az > ay) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("UP!\n");
			}
			ox = ax, oy = ay, oz = az;
		} else if(ax < 0 && ay < 0 && az < 0) {
			if(close_to(0.01, ox, ax) == TRUE && close_to(0.01, oy, ay) == TRUE) {
				printf("BACK!\n");
			}
			ox = ax, oy = ay, oz = az;
		}
		*/
		
		
		/*
		You would be wise (mainly save time) if you copy your code to calculate the magnitude from last week
		 (lab 4) to this section.  You will also need to copy your prototypes and functions to the appropriate sections
		 in this program.   
		
		*/

		
		
	}


    return 0;
}

int numButtons(int b[6]) {
	int cnt = 0, i;
	
	/* we skip b[5] which is the slider, which is read for giggles, but not "pressed" */
	for(i = 0; i < 5; i+=1) {
		if(b[i] > 0) {
			cnt+=1;
		}
	}
	
	return cnt;
}

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


int close_to(double tolerance, double point, double value) {
	int close;
	
	if(value > point - tolerance && value < point + tolerance) {
		close = TRUE;
	} else {
		close = FALSE;
	}
	
	return close;
}

