#include <stdio.h>

int mult (int a, int b) {
	if ((b == 0) || (a == 0))
		return 0;
	if ((a < 0) && (b < 0))
		return mult (-a, -b);
	if ((a < 0) && (b > 0))
		return -mult (-a, b);
	if ((a > 0) && (b < 0))
		return -mult (a, -b);
	return mult (a, b - 1) + a;
}

int main () {
	int a, b;
	scanf ("%d %d", &a, &b);
	printf ("\nO produto de %d por %d eh: %d\n", a, b, mult (a, b));
	
	return 0;
}
