// lab7.c
//
// This is the outline for your program
// Please implement the functions given by the prototypes below and
// complete the main function to make the program complete.
// You must implement the functions which are prototyped below exactly
//  as they are requested.

#include <stdio.h>
#include <math.h>
#define PI 3.141592653589
#define ROLL 0
#define PITCH 1
#define TRUE 1
#define FALSE 0

//NO GLOBAL VARIABLES ALLOWED


//PRE: Arguments must point to double variables or int variables as appropriate
//This function scans a line of explore data, and returns
//  True when left button is pressed
//  False Otherwise
//POST: it modifies its arguments to return values read from the input line.
int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT);

// PRE: -1.0 <= x_mag <= 1.0
// This function computes the roll of the esplora in radians
// if x_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double roll(double x_mag);

// PRE: -1.0 <= y_mag <= 1.0
// This function computes the pitch of the esplora in radians
// if y_mag outside of -1 to 1, treat it as if it were 1 or -1
// POST: -PI/2 <= return value <= PI/2
double pitch(double y_mag);


// PRE: -PI/2 <= rad <= PI/2
// This function scales the roll value to fit on the screen
// POST: -39 <= return value <= 39
int scaleRadsForScreen(double rad);

// PRE: num >= 0
// This function prints the character use to the screen num times
// This function is the ONLY place printf is allowed to be used
// POST: nothing is returned, but use has been printed num times
void print_chars(int num, char use);

//PRE: -39 <= number <=39
// Uses print_chars to graph a number from -39 to 39 on the screen.
// You may assume that the screen is 80 characters wide.
void graph_line(int number);

//calculates magnitude of x,y,z values
double mag(double x,double y,double z);

int main()
{
	double x, y, z;			// magnitude values of x, y, and z accelerations
	int b_Up, b_Down, b_Left, b_Right, t, r_p_mode, last_b, acc_var, t1, t2, t3, t4, ta, tb;	// variables to hold the button statuses
	double roll_rad, pitch_rad;		// value of the roll measured in radians
	int scaled_value; 	// value of the roll adjusted to fit screen display
	char to_print;

	//insert any beginning needed code here
	r_p_mode = ROLL;
	do
	{
		
		acc_var = read_acc(&x, &y, &z, &t, &b_Up, &b_Down, &b_Left, &b_Right);

		if(b_Up == 1 && last_b != 1) {
			if(r_p_mode == PITCH) {
				r_p_mode = ROLL;
				//printf("ROLL\n");
			} else if(r_p_mode == ROLL) {
				r_p_mode = PITCH;
				//printf("PITCH\n");
			}
		}
		
		roll_rad = roll(x);
		pitch_rad = pitch(y);

		
		if(r_p_mode == ROLL) {
			scaled_value = scaleRadsForScreen(roll_rad);
		} else if(r_p_mode == PITCH) {
			scaled_value = scaleRadsForScreen(pitch_rad);
		}

		if(r_p_mode == ROLL) {
			to_print = 'r';
		} else if(r_p_mode == PITCH) {
			to_print = 'l';
		}
		print_chars(scaled_value, to_print);

		fflush(stdout);
		last_b = b_Up;
	} while (acc_var == FALSE); // Modify to stop when left button is pressed
	return 0;
}

int read_acc(double* a_x, double* a_y, double* a_z, int* time, int* Button_UP, int* Button_DOWN, int* Button_LEFT, int* Button_RIGHT) {
	int  b_No, b_Slide;
	scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", time, a_x, a_y, a_z, Button_DOWN, Button_UP, Button_LEFT, Button_RIGHT, &b_No, &b_Slide );
	int tf;
	if(*Button_LEFT == 1) {
		tf = TRUE;
	} else {
		tf = FALSE;
	}
	return tf;
}

double roll(double x_mag) {
	double val; 
	if(x_mag <= -1) {
		val = asin(-PI/2);
	} else if(x_mag >= 1) {
		val = asin(PI/2);
	} else {
		val = asin(x_mag);
	}
	
	return val;
}

double pitch(double y_mag) {
	double val; 
	if(y_mag <= -1) {
		val = asin(-PI/2);
	} else if(y_mag >= 1) {
		val = asin(PI/2);
	} else {
		val = asin(y_mag);
	}
	
	return val;
}

int scaleRadsForScreen(double rad){ 
	double scalar = (PI/2)/39;
	int output;
	
	if(rad <= -PI/2) {
		output = -39;
	} else if(rad >= PI/2) {
		output = 39;
	} else {
		output = rad/scalar;
	}
	
	//printf("%lf\n%lf\n%d\n", rad, scalar, output);
	//sometimes is nan?
	
	return output;
}

void print_chars(int num, char use){ 
	int i, diff, p_num;
	if(num > 0) {
		for(i=0;i<39;i++) {
			printf(" ");
		}
		for(i=0;i<num;i++) {
			printf("%c", 'r');
		}
	} else if(num < 0) {
		p_num = abs(num);
		diff = 39-p_num;
		for(i=0;i<diff;i++) {
			printf(" ");
		}
		for(i=0;i<p_num;i++) {
			printf("%c", 'l');
		}
	} else if(num == 0) {
		for(i=0;i<39;i++) {
			printf(" ");
		}
		printf("0");
	}
	printf("\n");
}

void graph_line(int number){ 
	/* 
	maybe i'm missing something here, but this won't have a char to give print_char...?
	also apparently i'm over-powering print_chars
	
	*/
}

double mag(double x,double y,double z) {
	return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
}