/* Lab 4 Wrapper Program */

#include <stdio.h>
#include <math.h>

#define TRUE 1

int numButtons(int b[6]);

int main(void) {
	//int t;
	int b[6];
	int num;


	while (TRUE) {
		scanf("%d, %d, %d, %d, %d, %d", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);
		num = numButtons(b);
		printf("%d buttons pressed.\n", num);
		fflush(stdout);
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
