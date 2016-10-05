// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <string.h>

// Mathematical constants
#define PI 3.14159

/* Screen geometry
Use NUMROWS and NUMCOLS for the screen height and width (set by system)
*/
#define NUMROWS 80
#define NUMCOLS 100

/* Character definitions */
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '
#define WAIT_TIME 300
#define TRUE 1
#define FALSE 0
#define MAXPOINTS 10000
#define BUFF_LENGTH 10
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4

/*Number of samples taken to form an average for the accelerometer data
Feel free to tweak this.  You may actually want to use the moving averages
code you created last week along with this number as your windowing size
to get a playable game*/
#define NUM_SAMPLES 10  


/* 2D character array which the maze is mapped into
 You should fill this with characters, not numbers. */
char MAZE[NUMROWS][NUMCOLS];


/* PRE: The level of difficulty will be entered on the command line. 
You will have to use the argument to the command line to determine how 
difficult the maze is (how many maze characters are on the screen).
POST: Generates a random maze structure into MAZE[][]
You will want to use the rand() function and maybe use the output %100. */
void generate_maze(int difficulty);

/* PRE: MAZE[][] has been initialized by generate_maze()
POST: Draws the maze to the screen.  You must use the draw_character
function to print to the screen.  You cannot use printf in curses.  */
void draw_maze(void);

/* PRE: 0 < x < NUMCOLS, 0 < y < NUMROWS, characters are defined above
POST: Draws character use to the screen and position y,x as in a graph
where x is the horizontal axis and y is the vertical axis.  
When using the i and j from the maze, you will want to remember that 
i (outer loop) is the rows and corresponds to y, while j is the columns 
and corresponds to x.  */
void draw_character(int x, int y, char use);

/* PRE: -1.0 < x_mag < 1.0
POST: Returns tilt magnitude scaled to -1.0 -> 1.0
You may want to reuse the roll function written in previous labs. */ 

double calc_roll(double x_mag);

// compute the average of the first num_items of buffer
double avg(double buffer[], int num_items);

//update the max and min of the first num_items of array
void maxmin(double array[], int num_items, double* max, double* min);

//shift length-1 elements of the buffer to the left and put the 
//new_item on the right.
void updatebuffer(double buffer[], int length, double new_item);

int close_to(double tolerance, double point, double value);

int scrub_lines(int posx, int posy);

// Main - Run with './explore.exe -t -a -b' piped into STDIN
void main(int argc, char* argv[])
{
	int difficulty, ax, ay, moving;
	if(argc > 1) {
		difficulty = atoi(argv[1]);
	} else {
		printf("Please provide an argument for difficulty\n");
		exit(-1);
	}
	
	// setup screen    
	initscr();
	refresh();

	// Generate and draw the maze, with initial avatar
	generate_maze(difficulty);
	draw_maze();
	ay = 0;
	ax = NUMCOLS/2;
	
	// Read accelerometer data to get ready for using moving averages.  
	int b[6];
	//avatar x, avatar y : ax, ay
	int t;
	double x, y, z, avg_x, avg_y, avg_z, xmin, xmax, ymin, ymax, zmin, zmax;
	double arr_x[MAXPOINTS], arr_y[MAXPOINTS], arr_z[MAXPOINTS];
	
	
	// Event loop
	char next_char = MAZE[ay][ax];
	int alt_y = ay;
	int alt_x = ax;
	int last_t, first;
	char txt[25];
	first = TRUE;
	
	do
	{	
		// Read data, update average
		scanf("%d, %lf, %lf, %lf, %d, %d, %d, %d, %d, %d", &t, &x, &y, &z, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5] );
		if(first == TRUE) {
			last_t = t;
			first = FALSE;
		}
		if(t - last_t >= WAIT_TIME) {
			moving = TRUE;
			last_t = t;
		} else {
			moving = FALSE;
		}
		
		//do the average-y stuffs
		updatebuffer(arr_x, BUFF_LENGTH, x);
		updatebuffer(arr_y, BUFF_LENGTH, y);
		updatebuffer(arr_z, BUFF_LENGTH, z);
		
		avg_x = avg(arr_x, BUFF_LENGTH);
		avg_y = avg(arr_y, BUFF_LENGTH);
		avg_z = avg(arr_z, BUFF_LENGTH);
		
		maxmin(arr_x, BUFF_LENGTH, &xmax, &xmin);
		maxmin(arr_y, BUFF_LENGTH, &ymax, &ymin);
		maxmin(arr_z, BUFF_LENGTH, &zmax, &zmin);
		
		int move_dir = NONE;
		int valid = TRUE;

		//tol point val
		 //if(ax+1 < NUMCOLS && ax-1 > 0)
			if(close_to(0.5, 1, x) == TRUE && ax > 0) {
				move_dir = LEFT;
			} else if(close_to(0.5, -1, x) == TRUE && ax+1 < NUMCOLS) {
				move_dir = RIGHT;
			}
		
		
			if(move_dir == LEFT) {
				if(MAZE[ay][ax-1] == '*') {
					move_dir = NONE;
				}
			} else if(move_dir == RIGHT) {
				if(MAZE[ay][ax+1] == '*') {
					move_dir = NONE;
				}
			}
		
		
		
		// Is it time to move?  if so, then move avatar
		if(moving == TRUE) {	
			draw_character(alt_x, alt_y, next_char);
			draw_character(ax, ay, AVATAR);
			//otherwise it's off-screen
			
			
			if(ay+1 < NUMROWS) {
				alt_y = ay;
				
				if(MAZE[ay+1][ax] != '*') {
					ay++;
				}
				
				 
					alt_x = ax;
					if(move_dir == LEFT) {
						ax--;
					} else if(move_dir == RIGHT) {
						ax++;
					} else {
						ax = ax;
					}
				
				//no diagonals
				if(y != alt_y && x != alt_x) {
					y = alt_y;
				}
				next_char = MAZE[alt_y][alt_x];
			}
			if(ay == NUMROWS-1) {
				strcpy(txt, "YOU WIN!\n");
				break;
			} else if(MAZE[alt_y][alt_x-1] == WALL && MAZE[alt_y][alt_x+1] == WALL && MAZE[alt_y+1][alt_x] == WALL) {
				strcpy(txt, "YOU LOSE!\n");
				break;
			} /*else if(scrub_lines(alt_x, alt_y) == FALSE) {
				strcpy(txt, "YOU LOSE!\n");
				break;
			}*/
		}
		refresh();
		
	} while(1); // Change this to end game at right time 

	// Print the win message
	endwin();
	
	printf("%s", txt);
}


void generate_maze(int difficulty) {
	srand(time(NULL));
	int n, i, h;
	for(i=0;i<NUMROWS;i++) {
		for(h=0;h<NUMCOLS;h++) {
			n = rand() % 100;
			if(n < difficulty) {
				MAZE[i][h] = WALL;
			} else {
				MAZE[i][h] = EMPTY_SPACE;
			}
		}
	}
	
}

void draw_maze(void) {
	int i, h, x, y;
	for(i=0;i<NUMROWS;i++) {
		for(h=0;h<NUMCOLS;h++) {
			draw_character(h, i, MAZE[i][h]);
		}
	}
	refresh();
}


/* PRE: 0 < x < NUMCOLS, 0 < y < NUMROWS, characters are defined above
POST: Draws character use to the screen and position y,x as in a graph
where x is the horizontal axis and y is the vertical axis.  
When using the i and j to draw the maze, you will want to remember that 
i (outer loop) is the rows and corresponds to y, while j (the inner loop) is the columns 
and corresponds to x. 

This code places the Avatar and the maze on the screen.  

IT WORKS CORRECTLY AS PROVIDED.  
PLEASE DO NOT CHANGE THIS FUNCTION. */

void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

double calc_roll(double x_mag) {
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

double avg(double buffer[], int num_items) {
	double avg = 0;
	int i;
	for(i = 0; i < num_items; i+=1) {
		avg = (avg + buffer[i])/2.0;
	}
	return avg;
}

void maxmin(double array[], int num_items, double* max, double* min) {
	int i;
	for(i = 0; i < num_items; i+=1) {
		if(array[i] > *max) {
			*max = array[i];
		}
		if(array[i] < *min) {
			*min = array[i];
		}
	}
}

void updatebuffer(double buffer[], int length, double new_item) {
	//double nbuf[MAXPOINTS];
	int i;
	for(i = 0; i < length-1; i+=1) {
		buffer[i] = buffer[i+1];
	}
	buffer[length-1] = new_item;
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

int scrub_lines(int posx, int posy) {
	int safe = FALSE;
	int limr, liml;
	
	//check for range on current x line
	int i;
	for (i = posx; i < NUMCOLS; i++) {
		if(MAZE[posy][i] == WALL) {
			limr = i;
			break;
		}
	}
	for (i = posx; i > 0; i--) {
		if(MAZE[posy][i] == WALL) {
			liml = i;
			break;
		}
	}
	//check for an opening under and in range
	for (i = liml+1; i < limr; i++) {
		if(MAZE[posy+1][i] != WALL) {
			safe = TRUE;
		}
	}
	if (MAZE[posy+1][posx] != WALL) {
		safe = TRUE;
	}
	
	return safe;
}
