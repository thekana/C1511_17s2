// Print out an array.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void showArray (int size, int array[MAX_LENGTH]);

// DO NOT CHANGE THIS MAIN FUNCITON
int main (int argc, char *argv[]) {
    // get array size
    int size;
    printf ("Enter array size: ");
    scanf ("%d", &size);

    // declare array
    int array[MAX_LENGTH];

    printf ("Enter array values: ");
    // intialise array values
    int i = 0;
    while (i < size) {
        scanf ("%d", &array[i]);
        i++;
    }

    showArray (size, array);

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

// this function prints the array in the format
// [1, 2, 3, ...]
void showArray (int size, int array[MAX_LENGTH]) {
    printf("[");
    int i=0;
    while (i<size) {
        if(i==(size-1)) {
            printf("%d]\n",array[i]);
        } else {
            printf("%d, ",array[i]);
        }
        i++;
    }

}
