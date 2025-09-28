#include <stdio.h>
#include <math.h>

int main () {
	int a, b, c;
	float p;
	scanf ("%d %d %d", &a, &b, &c);
	p = (a + b + c) / 2;
	printf ("%.3f\n", sqrt( p * (p - a) * (p - b) * (p - c)));
	
	return 0;
}
