#include <stdio.h>

int main () {
    int buffer[10];
    FILE *file = fopen ("output.txt", "rb");
    fread (buffer, sizeof(int), 10, file);
    fclose(file);

    for (int i = 0; i < 10; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    return 0;
}