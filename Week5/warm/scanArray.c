// Scan in an array.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void scanArray (int size, int array[MAX_LENGTH]);
void showArray (int size, int array[MAX_LENGTH]);

// DO NOT CHANGE THIS MAIN FUNCITON
int main (int argc, char *argv[]) {
    // get array size
    int size;
    printf ("Enter array size: ");
    scanf ("%d", &size);

    // declare array
    int array[MAX_LENGTH];

    // get values
    printf ("Enter array values: ");
    scanArray (size, array);

    // print values
    showArray (size, array);

    return EXIT_SUCCESS;
}

// END OF MAIN FUNCTION

// this function reads in values from
// standard input into an array
void scanArray (int size, int array[MAX_LENGTH]) {
    int i=0;
    while(i<size) {
        scanf("%d",&array[i]);
        i++;
    }
}

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

