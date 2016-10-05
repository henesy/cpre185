/*     Sean Hinchee
    seh@iastate.edu
    CPRE 185 Section 58
Programming Practice 3
     <Reflection 1 What were you trying to learn or achieve?>
        I was attempting to learn about loops and functions. Writing prototypes was reinforced as well, showing a function could be prototyped before it is defined. I was attempting to learn how to use loops within loops as well.
    <Reflection 2 Were you successful? Why or Why not?>
         I was successful. My code compiled successfully after some minor refining due to simple mistakes such as typographic errors due to writing expediently. 
    <Reflection 3 Would you do anything differently if starting this program over? If so, explain what.>
       Originally I would have said I would have used fewer if statements, but I reduced my number by the end of the program by using two more variables, chk_h and chk_w. If I had to do something over I would make the program print a pyramid/triange shape rather than just a square.
    <Reflection 4 Think about the most important thing you learned when writing this piece of code. What was it and explain why it was significant.>
        I learned to pay attention to subtle differences in variable names when typing out statements rapidly. Even if a quick solution is desired, taking ones time is always worth the effort. The experience was significant because it caused my code to not run in certain scenarios, chk_h and chk_w were typo'd a few times as chk_h where chk_w should have been originally in the if statement. 
<Other questions/comments for Instructors>
        None.
*/

#include <stdio.h>

void print_out(char, int, int);

int num_check(int, char);

int main() {
    char c;
    int h, w, chk_w, chk_h;

    printf("Character to print: ");
    scanf("%c", &c);

    printf("Height: ");
    scanf("%d", &h);

    printf("Width: ");
    scanf("%d", &w);

    chk_w = num_check(w, 'w');
    chk_h = num_check(h, 'h');
    
    if(chk_h == 0 && chk_w == 0) {
        print_out(c, h, w);
    } else {
        printf("The numbers you entered were not valid. 80x24 is the limit on height x width dimensions.\n");
    }
    
    return 0;
}

void print_out(char c, int h, int w) {
    int i, j;
    
    /* h = 24 and w = 80 should be the max dimensions */
    for(i = 0; i < h; i+=1) {
        for(j = 0; j < w; j+=1) {
            printf("%c", c);
        }
        printf("\n");
    }
}

int num_check(int num, char var) {
    int tf;
    
    /* 24x80 is the standard terminal size, make sure it does not exceed
     * the standard size 
     * true is 1; false is 0
     * if true, num exceeds what it should be */
    if(var == 'h') {
        if(num > 24) {
            tf = 1;
        } else {
            tf = 0;
        }
    } else if(var == 'w') {
        if(num > 80) {
            tf = 1;
        } else {
            tf = 0;
        }
    }
    return tf;
}


