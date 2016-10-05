// Lab 10 ExTalker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses/ncurses.h>
#define MAXWORDS 100
#define WORDLEN 11
#define DEBUG 0   // set to 0 to disable debug output
#define PLYR '>'
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define NONE 4
#define TRUE 1
#define FALSE 0
#define WAIT_TIME 300
#define PRESS_WAIT_TIME 600

// reads words from the file
// into wl and trims the whitespace off of the end
// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename); 

//modifies s to trim white space off the right side
// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) ;

void draw_character(int x, int y, char use);

void wipe(char *arr, int len);

//mvprintw(y,x,"%d <- number", i);

void backspace(char arr[80]);

void undo(char arr[80], int num);

int main(int argc, char* argv[]) {
	char* wordlist[MAXWORDS];
	int wordCount;
	int i;

	wordCount = readWords(wordlist, argv[1]);

	if (DEBUG) {
		printf("Read %d words from %s \n",wordCount, argv[1]);
		for (i = 0; i< wordCount; i++) {
			printf("%s,", wordlist[i]);

		}
		printf("\n");
		}

	//down, up, left, right
	int b[6];
	//down, up, left, right, blah1, blah2
	int j[6];
	int t, last_t, x, y, track, cx, cy, cd, moving, first, loc, pressed;
	cy = 0, cx = 0;
	char sentence[80];
	wipe(sentence, 80);
	strcpy(sentence, "");
	char currword[11];
	char tmp[15];
	wipe(tmp, 15);
	wipe(currword, 11);
	initscr();
	refresh();
	first = TRUE;
	pressed = FALSE;
	int ladded;
	int swtch = 1;
	char changes[100][80];
	int rev = 0;
	
	do {
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &j[0], &j[1], &j[2], &j[3], &j[4], &j[5]);
		if(first == TRUE) {
			last_t = t;
			first = FALSE;
		}
		if(t - last_t >= WAIT_TIME) {
			moving = TRUE;
			if(swtch == 1) {
				pressed = FALSE;
				swtch = 0;
			} else if( swtch == 0) {
				swtch = 1;
			}
			last_t = t;
		} else {
			moving = FALSE;
		}

		
		y = 0, x = 0, track = 0;
		for(i = 0; i < wordCount; i++) {
			mvprintw(y, x, "%15s", wordlist[i]);
			x+=15;
			track++;
			if(track == 5) {
				//mvprintw(y, x, "\n");
				y++;
				x=0;
				track=0;
			}
		}

		mvprintw(cy, cx, "%c", PLYR);
		cd = NONE;
		if(j[0] > 0) {
			cd = DOWN;
		} else if(j[1] > 0) {
			cd = UP;
		} else if(j[2] > 0) {
			cd = LEFT;
		} else if(j[3] > 0) {
			cd = RIGHT;
		}
		
		wipe(currword, 11);
		
		loc = cx/15 + cy*5;
		//currword = wordlist[loc];
		strcpy(currword, wordlist[loc]);
		//mvprintw(17, 0, "%s", currword);
		
		if(moving == TRUE) {
			if(cd == DOWN && cy < 15) {
				cy++;
			} else if(cd == UP && cy > 0) {
				cy--;
			}
			if(cd == LEFT && cx > 0) {
				if(cx-15 > -1) {
					cx-=15;
				}
			} else if(cd == RIGHT && cx < 80) {
				if(cx+15 < 75) {
					cx+=15;
				}
			}
		}
		/*
		if(pressed == FALSE) {
			//up
			if(b[1] > 0) {
				wipe(tmp, 15);
				strcpy(tmp, " ");
				strcat(tmp, currword);
				strcat(sentence, tmp);
				//mvprintw(17, 0, "%s", tmp);
				pressed = TRUE;
			} else if(b[0]) {
				backspace(sentence);
				pressed = TRUE;
			} else if(b[2]) {
				wipe(tmp, 15);
				strcpy(tmp, "");
				strcat(tmp, currword);
				strcat(sentence, tmp);
				pressed = TRUE;
			}
		}*/
		if(pressed == FALSE) {
			//up
			if(b[1] > 0) {
				rev++;
				wipe(tmp, 15);
				strcpy(tmp, " ");
				strcat(tmp, currword);
				strcpy(changes[rev], tmp);

				//mvprintw(17, 0, "%s", tmp);
				pressed = TRUE;
			} else if(b[0]) {
				strcpy(changes[rev], "");
				rev--;
				pressed = TRUE;
			} else if(b[2]) {
				rev++;
				wipe(tmp, 15);
				strcat(tmp, currword);
				strcpy(changes[rev], tmp);
				pressed = TRUE;
			}
		}
		int k;
		wipe(sentence, 80);
		strcpy(sentence, "");
		for(k = 0; k <= rev; k++) {
			strcat(sentence, changes[k]);
		}
		mvprintw(16, 0, "%s", sentence);
		refresh();
	} while(1);
	
	refresh();
	endwin();
    return 0;
	}

// DO NOT MODIFY THIS FUNCTION
void trimws(char* s) {
        int len = strlen(s) ;
        int x;
        if (len ==0) return;
        x = len-1;
        while (isspace(s[x]) && (x>=0)) {
                s[x] = '\0';
                x--;
                }
        }


// DO NOT MODIFY THIS FUNCTION
int readWords(char* wl[MAXWORDS], char* filename) {
	int numread =0;
	char line[WORDLEN];
	char *p;
	FILE* fp = fopen(filename,"r");
	while (!feof(fp)) {
		p  =fgets(line, WORDLEN, fp);
		if (!feof(fp) && p !=NULL) {
			trimws(line);
			wl[numread] = (char *)  malloc(strlen(line)+1);
			strcpy(wl[numread], line);
			numread++;
			}
		} 
	fclose(fp);
	return numread;	
}

void draw_character(int x, int y, char use)
{
	mvaddch(y,x,use);    
	refresh();
}

void wipe(char *arr, int len) {
	int i;
	for(i = 0; i < len; i++) {
		arr[i] = 0;
	}
	arr[0] = '\0';
}

void backspace(char arr[80]) {
	int i;
	size_t pos = strlen(arr);
	for(i = (int)pos; i >= 0; i--) {
		if(arr[i] == ' ') {
			arr[i] = '\0';
			break;
		}
	}
	for(i = i+1; i < 80; i++) {
		arr[i] = 0;
	}
}

void undo(char arr[80], int num) {
	int i;
	size_t pos = strlen(arr);
	int start = (int)pos;
	for(i = start; i >= 0; i--) {
		if((start - i) == num) {
			arr[i] = '\0';
			break;
		}
	}
	for(i = i+1; i < 80; i++) {
		arr[i] = 0;
	}
}
