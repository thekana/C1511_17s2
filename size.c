#include <stdio.h>
#include <stdlib.h>
int main () {
    int *a = (int *)malloc(15 * sizeof(int));
    int i;
    printf("%p\n",&a[0]);
    printf("%p\n",&a[1]);
    printf("%p\n",&a[5]);
    printf("%p\n",&a[15]);
    for (i = 0; i < 4; i++) {
        a++;
        a[i] = i;
    }
    printf("%d\n", a[1]);
}
