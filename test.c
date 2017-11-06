#include <stdio.h>
#include <stdlib.h>

int main () {
    printf("Enter rainfall: ");
    int i=0;
    int sum=0;
    int wet=0;
    int c = 0;
    while (scanf("%d", &c) != EOF) {
        i++;
        sum = sum + c;
        if (c>5) {
            wet++;
        }
        //c = getchar();
    }
    double avg = 0;
    avg = sum/i;
    printf("Days: %d Total rainfall: %dmm Average rainfall: %.2lfmm Wet days: %d\n",i,sum,avg,wet);
}
