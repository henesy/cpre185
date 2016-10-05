#include <stdio.h>
#include <math.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define UP 2
#define DOWN 3
#define LEFT 4
#define RIGHT 5
#define FRONT 6
#define BACK 7

double mag(double x,double y,double z);
int close_to(double tolerance, double point, double value);

int main() {
	int t, ti, printed, timing, falling, k = 1000, last_print;
	double time_start, time_stop, ax, ay, az, msec, vi, xi;
	int b[6];
	vi = 0;
	printed = FALSE, falling == FALSE;
	last_print = 0;
	while(TRUE) {
		//scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", &t, &ax, &ay, &az, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5] );
		scanf("%d, %lf, %lf, %lf", &t, &ax, &ay, &az);
		if(printed == FALSE) {
			printf("Now receiving data\nWaiting");
			printed = TRUE;
		}
		if(last_print == 0) {
			last_print = t;
			ti = t;
			vi = 0;
			xi = 0;
		}
		if(close_to(10, last_print+k, t) == TRUE) {
			if(falling == FALSE) {	
				printf(".");
			} else {
				printf("!");
			}
			last_print = t;
		}
		
		if((close_to(0.3, 0, mag(ax,ay,az))) == TRUE) {
			if(falling == FALSE) {
				printf("\nI'm falling");
				time_start = t;
			}
			
			falling = TRUE;
		} else {
			if(falling == TRUE && close_to(0.3, 1, mag(ax,ay,az)) == TRUE) {
				double diff, altvel, vel, altpos;
				time_stop = t;
				
				//printf("\n%lf, %lf", time_stop, time_start);
				diff = (time_stop - time_start)/1000.0;
				
				//vel = (double)(0.0 + (mag(ax,ay,az)*diff) + (1.0/2.0) * (9.8) * diff * diff);
				vel = ((1.0/2.0) * (9.8) * diff * diff);
				
				altvel = vi + (9.8)*(1 - mag(ax,ay,az))*((t-ti)/1000);
				
				altpos = xi + altvel*((t-ti)/1000);
				
				printf("\nOuch! I fell %lf meters in %lf seconds.", vel, diff);
				printf("\nCompensating for air resistance, the fall was %lf meters.", altpos);
				printf("\nThis is %.2lf%% less than before.", (((altpos/vel)*100)-100));
			
				break;
			}
			//time_stop = t;
			//falling = FALSE;
		}
		// k = 1 s; print every second; so every k = 1000 ms
		/*
			When the values are near 2, the Esplora is falling.
			The Esplora prints every 2-3 milliseconds (average is ~2 visually)
		*/
		/* 
			x1 = x0 + vt + (1/2) gt^2
			x1 -> solve for
			x0 -> 0
			v -> mag(x,y,z)
			t -> difftime(timer,)
			g -> -9.8 m/s^2
			t -> difftime(timer,)
		*/
		if(falling == TRUE) {
			vi = vi + (9.8)*(1 - mag(ax,ay,az))*((t - ti)/1000);
			xi = xi + vi*((t-ti)/1000);
			ti = t;
		}
		
		fflush(stdout);

	}
	
	
	
	return 0;
}


double mag(double x,double y,double z) {
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
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