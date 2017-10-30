#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a=0,b=0,n=0,i=0,j=0,size=0;
    printf("Enter the flag size: ");
    scanf("%d",&size);
    while(i<=4*size-2){
        if(i!=2*size-1){
            while(j<=9*size-2) {
                if (j==3*size-1) {
                    printf("  ");
                } else { printf("#");}
                j++;
            }
            j=0;
        } else {while(a<=18*size-1) {
                    printf(" ");
                    a++;
                    if(a==9*size) {
                        printf("\n");
                    }
                }
        }
    i++; printf("\n");
    }
}
