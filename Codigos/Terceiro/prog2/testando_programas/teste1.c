#include <stdio.h>
#include <assert.h>

int main() {
    int i;
    for (i=3; i<=10; i++) {
        assert(i <= 7);
        printf("i = %d\n", i);
    }
    return 0;
}