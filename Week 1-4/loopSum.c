#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    int n=0,i=0,sum=0,j=0;

    printf("How many numbers: ");
    scanf("%d",&n);
    while(i<=n-1) {
        scanf("%d",&j);
        sum+=j;
        i++;
    }
    printf("%d\n",sum);
    return EXIT_SUCCESS;
}
