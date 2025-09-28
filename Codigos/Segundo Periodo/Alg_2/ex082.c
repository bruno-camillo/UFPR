#include <stdio.h>

int horas (int a) {
	return a / 3600;
}

int minutos (int a) {
	return (a % 3600) / 60;
} 

int segundos (int a) {
	return (a % 3600) % 60;
}

int main () { 
	int a;
	scanf ("%d", &a);
	printf ("%d:%d:%d\n", horas(a), minutos(a), segundos(a));
	
	return 0;
}	
