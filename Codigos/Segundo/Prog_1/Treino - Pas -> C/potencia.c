#include <stdio.h>

float pot (float x, int n) {
	if (n == 0) 
		return 1;
	return x * pot(x, n - 1);  
}

float potencia (float x, int n) {
	int i = 1;
	float k = 1;
	while (i <= n, i++) 
		k = k * x
	return k;
}

int main () {
	float a;
	int b;
	scanf ("%f %d", &a, &b);
	printf ("\n%.2f elevado a %d eh igual a %.2f\n", a, b, pot(a, b));
	
	return 0;
}
