#include <stdio.h>
#include <stdlib.h>

int main ( ) {

int hour=1515;
int zone=845;
int formatted, min;
    //take mins from hour and zone then add them together and mod 60 to make sure the result is not over 60
    min = (hour%100+zone%100)%60;
    //Now do the same for hour
    formatted = 100*((hour / 100 + zone / 100) % 24 + (hour % 100 + zone % 100) / 60) + min;

printf("%d",formatted);

}
