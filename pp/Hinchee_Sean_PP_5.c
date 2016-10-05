/*  Sean Hinchee
    seh@iastate.edu
    CPRE 185 Section 58
	Programming Practice 5
     <Reflection 1 What were you trying to learn or achieve?>
		In the fifth programming practice I was attempting to learn about using character arrays and string functions in a practical manner. Additionally, I was attempting to achieve creation of a functional program using string and character functions and a prototype for a function.
    <Reflection 2 Were you successful? Why or Why not?>
		My attempt at the creation of a program encompassing my goals was successful. The code compiled and ran with only three or four periods of debugging attempting to refine the code and resolve a few stray, unforeseen, errors.
    <Reflection 3 Would you do anything differently if starting this program over? If so, explain what.>
		If I could do anything different in this assignment I would create, perhaps, a program which attempts to pseudo-randomly mix the letters of the names given into bizarre strings.
    <Reflection 4 Think about the most important thing you learned when writing this piece of code. What was it and explain why it was significant.>
		I think the most important thing I learned was a re-affirmation of type casting as a method for debugging and that clearing out an array prior to its use is a critical step with strings. Prior to the for() loop near the beginning of main(), the names had odd characters pinned onto them after being flipped. An alternate solution may have been to pass the strlen() size_t values to the name-flipping function as an array in parallel to the names array, providing a guiding number of characters and/or a place to begin operation within the arrays to flip them. After clearing the array, the stray characters were missing and all was well, it was a lesson well learned.
<Other questions/comments for Instructors>
	I was unclear on what exactly qualified as a "character" function in juxtaposition to a "string" function as I interpreted them as synonymous. A string is an array of characters, thus I assumed it was intended that functions that are not necessarily intended for strings such as memcpy() were the intended type of function.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define SLEN 50
#define NNAMES 5

void name_flip(char arr[NNAMES][SLEN]);


int main(int argc, char *argv[]) {
	//5 names; 50 chars per name
	char names[NNAMES][SLEN];
	int i, j;
	
	for (i = 0; i < NNAMES; i++) {
		//printf("Clearing array %d\n", i);
		for (j = 0; j < SLEN; j++) {
			names[i][j] = '\0';
		}
	}

	printf("You will be prompted to enter %d names which must be less than %d characters long.\n", NNAMES, SLEN); 
	for (i = 0; i < NNAMES; i++) {
		printf("Name: ");
		scanf("%s", &names[i]);
	}
	
	printf("Your names will now be flipped.\n");
	
	name_flip(names);
	
	printf("Here are your names: \n");
	for (i = 0; i < NNAMES; i++) {
		printf("%s\n", names[i]);
	}
	
	printf("Good bye! ☺\n");
	
	return 0;
}


void name_flip(char arr[NNAMES][SLEN]) {
	char tmp[SLEN];
	char newstr[SLEN];
	int i, j, k;

	for (i = 0; i < NNAMES; i++) {
		memset(tmp, 0, sizeof(tmp));
		memset(newstr, 0, sizeof(tmp));
		//character function
		memcpy(tmp, arr[i], sizeof(tmp));
		
		k=0;
		for (j = SLEN-1; j >= 0; j--) {
			/*if(tmp[j] > 64 && tmp[j] < 173) {*/
			//a function involving a singular character?
			if(isalpha(tmp[j])) {
				newstr[k] = tmp[j];
				k++;
			}
		}
		//string function
		/* 
			casting exists because the compiler refused to compile using string.h if the given arrays were not of type char * (size __restrict__ or something like that) and the arrays were of type char (*)[50]
		*/
		strcpy((char * __restrict__)arr[i], (char * __restrict__)newstr);
	}
}

