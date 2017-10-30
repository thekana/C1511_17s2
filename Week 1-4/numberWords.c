//Numbers to Words
//Kanadech Jirapongtanavech (z5176970), JIAYI SI(z5142102)
//Zain Afzal (F09A)
//4/8/2017

#include <stdio.h>
#include <stdlib.h>
int main (int argc, char *argv[]) {

    int n=0;
    printf("Please enter an integer: ");
    scanf("%d",&n);
    if(n>5){
        printf("You entered a number greater than five.\n");
    }
    else if(n<1){
        printf("You entered a number less than one.\n");
    }
    else if(n==1){
        printf("You entered one.\n");
    }
    else if(n==2){
        printf("You entered two.\n");
    }
    else if(n==3){
        printf("You entered three.\n");
    }
    else if(n==4){
        printf("You entered four.\n");
    }
    else if(n==5){
        printf("You entered five.\n");
    }
    return EXIT_SUCCESS;
}

