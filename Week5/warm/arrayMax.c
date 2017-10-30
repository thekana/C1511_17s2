// Find the maximum value in an array.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

int arrayMax (int size, int array[MAX_LENGTH]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {
    // Get array size
    int size;
    printf ("Enter array size: ");
    scanf ("%d", &size);

    // Declare array
    int array[MAX_LENGTH];

    printf ("Enter array values: ");
    // Initialise array values
    int i = 0;
    while (i < size) {
        scanf ("%d", &array[i]);
        i++;
    }

    printf ("Maximum value is %d.\n", arrayMax (size, array));

    return EXIT_SUCCESS;
}

// Return the largest value in a given array.
int arrayMax (int size, int array[MAX_LENGTH]) {
    int max=array[0],i=0;
    while(i<size) {
        if(max < array[i]) {
            max=array[i];
        }
        i++;
    }
    return max;
}

