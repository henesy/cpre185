// CprE 185: Lab 3
// Problem 1: Mysterious Output

#include <stdio.h>

int main()
{
	int integerResult;
	double decimalResult;
	
	integerResult = 77 / 5;
	/* changed %lf to %d, as an integer was passed, not a long float */
    printf("The value of 77/5 is %d\n", integerResult);

	integerResult = 2 + 3;
    /* added a comma and the variable to pass to the %d */
	printf("The value of 2+3 is %d\n", integerResult);

	decimalResult = 1.0 / 22.0;
    /* changed %d to %lf, as a long float was passed, not a decimal */
	printf("The value 1.0/22.0 is %lf\n", decimalResult);
	
	return 0;
}
