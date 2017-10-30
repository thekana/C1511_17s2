#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main() {
    int i=9;
    float y=i;
    i=i/3;
    if(round(y)) {
        printf("Round was used %d\n",i);
    } else {
        printf("No");
    }
}
