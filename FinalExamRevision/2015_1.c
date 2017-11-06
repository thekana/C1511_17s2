#include <stdio.h>

int main(void) {
    int x=1;
    int y=0;
    while(x<100) {
        x = x+8*y++;
        printf("%d\n",x);
    }

    return 0;

}
