//A program to warm up
//Kanadech Jirapongtanavech (z5176970)
//Zain Afzal (F09A)
//2017-08-25

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    char a = ' ';

    while (a <=126) {
        printf("%03d 0x%02x %c\n",a,a,a);
        a++;
    }

    return EXIT_SUCCESS;
}
