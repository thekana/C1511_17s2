//Sort 3 numbers
//Kanadech Jirapongtanavech (z5176970) maerry(z5142102)
//Zain FO9A
//11/07/2017

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int a=0,b=0,c=0,max=0,min=0,mid=0;
    printf("Enter 3 numbers: ");
    scanf("%d%d%d",&a,&b,&c);
    if(a>=b&&b>=c){
        max=a;mid=b;min=c;
    } else if (a>=c && c>=b){
        max=a;
        mid=c;
        min=b;
    } else if (b>=c && c>=a){
        max=b;
        mid=c;
        min=a;
    } else if (b>=a && a>=c){
        max=b;mid=a;min=c;
    } else if (c>=a && a>=b){
        max=c;mid=a;min=b;
    } else {
        max=c;mid=b;min=a;
    }
    printf("%d\n%d\n%d\n",min,mid,max);
    return EXIT_SUCCESS;
}
