#include <stdio.h>
#include <stdlib.h>

int main () {
    int p=10;
    printf("%p\n",&p);
    int *a=&p;
    printf("%d\n",*a);
    *a=4;
    printf("%d\n",p);
}
