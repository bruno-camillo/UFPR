#include <stdio.h>

int main() {
    int buffer[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    FILE *file = fopen("output.txt", "wb");
    fwrite(buffer, sizeof(int), 10, file);
    fclose(file);

    return 0;
}