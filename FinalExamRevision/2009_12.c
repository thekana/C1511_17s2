#include <stdio.h>
void wondrous( int start) {
    printf("%d\n",start);
    while(start != 1) {
        if(start%2==0){
            start = start / 2;
            printf("%d\n",start);
        } else {
            start = start*3 +1;
            printf("%d\n",start);
        }
    }
}


int main(void) {
    wondrous(10);
}
