//A program to check a leap year
//Kanadech Jirapongtanavech (z5176970), JIAYI SI(z5142102)
//Zain Afzal (F09A)
//4/8/2017

#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    
    int year=0;
    
    printf("Enter a year after 1852: ");
    scanf("%d",&year);
    if (year<1852) {
        printf("%d is before 1852.\n",year);
    } else {
        if(year%4==0){
            if(year%100==0){
                if(year%400==0){
                    printf("%d is a leap year.\n",year);
                } else {
                    printf("%d is not a leap year.\n",year);
                }
            } else {
                printf("%d is a leap year.\n",year);
            }
        } else {
            printf("%d is not a leap year.\n",year);
        }
    }
    return EXIT_SUCCESS;
}

