/*      Sean Hinchee 
        seh@iastate.edu
        CPRE 185 Section G
        Programming Practice 4
        <Reflection 1 What were you trying to learn or achieve?>
            In programming practice 4 I was attempting to learn about the implementation and utilization of arrays, loops, and function prototypes. For extra credit, which is a definite goal to achieve, I was attempting to leverage additional pointers in function definitions and utilize multidimensional arrays.
        <Reflection 2 Were you successful? Why or Why not?>
            My attempt was successful as the code both compiled and ran without any error in my testing. Additionally the code appeared to be satisfying all constraints and recommendations provided. 
        <Reflection 3 Would you do anything differently if starting this program over? If so, explain what.>
            If I were restarting this programming practice over, I would have made a more original program rather than a name/age indexer. Additionally, if I were to repeat the same process, I would attempt to save the index to a file and allow editing of said pseudo-database/index.
        <Reflection 4 Think about the most important thing you learned when writing this piece of code. What was it and explain why it was significant.>
            I was reminded via gcc error output that "char **" in a function definition is not an allowable substitute for the specific size "(*)[51]" of the names array when it was passed. Additionally, I was reminded that "char (*) names[NAME_LEN]" is not an acceptable argument definition in a function definition, but is acceptable in a prototype without error. These lessons are significant as they are reminders of C's syntax details and specifics which help prevent future errors from cropping up in the first place, thus, optimally, saving time and brainpower.
        <Other questions/comments for Instructors>
            Some of the code was created intentionally redundant in an attempt it utilize a broader set of potential C semantic combinations.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMN 50
#define NAME_LEN 51

void addname(char [NUMN][NAME_LEN], char *, int *);

void addage(int *, int, int *);

void clr(char *);

int main() {

    //50 names and ages, 50 charcters per name
    char names[NUMN][NAME_LEN];
    int ages[NUMN];
    int i, h, pos, tmpi;
    char response[NAME_LEN];
    //blank is intentionally redundant as a Proof of Concept
    char blank[NAME_LEN] = "";
    //char stahp[NAME_LEN] = "stop";
    for(i=0;i<NUMN;i+=1) {
        //-1 indicates it was never "set" as an age
        ages[i] = -1;
    }
    
    pos = 0;
    while(pos < NUMN) {
        strcpy(response, blank);
        tmpi = -1;
        printf("Enter a name (\"stop\" to stop): ");
        scanf("%50s", &response);
        //fgets(response, (NAME_LEN - 1), stdin);
        if(strcmp(response, "stop") == 0) {
            break;
        }
        addname(names, response, &pos);
        printf("Enter an age: ");
        //perhaps use %s, atoi, and error checking with a sub-loop?
        scanf("%d", &tmpi);
        addage(ages, tmpi, &pos);
        pos+=1;
    }
    printf("\nStopping...\n");
    if(pos > 0) {
        printf("\nNames index: \n");
        for(h = 0; h < pos; h += 1) {
            printf("Name: %s\nAge: %d\n\n", names[h], ages[h]);
        }
    }
    return 0;
}


void addname(char arr[NUMN][NAME_LEN], char *val, int *pos) {
    memcpy(arr[*pos], val, NAME_LEN);
}


void addage(int *arr, int val, int *pos) {
    arr[*pos] = val;
}

void clr(char *str) {
    strcpy(str, "");
}


