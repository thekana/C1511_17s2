// Find and print the first, middle, and last elements of an array.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 1024

void printFirstMiddleLast (int size, int array[MAX_LENGTH]);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {
    // Get the array size.
    int size;
    printf ("Enter array size: ");
    scanf ("%d", &size);

    // Declare the array.
    int array[MAX_LENGTH];

    printf ("Enter array values: ");
    // Intialise the array values.
    int i = 0;
    while (i < size) {
        scanf ("%d", &array[i]);
        i++;
    }

    printFirstMiddleLast (size, array);

    return EXIT_SUCCESS;
}

// Print the first, middle, and last values of an array,
// on separate lines.
void printFirstMiddleLast (int size, int array[MAX_LENGTH]) {
    // Your code goes here!
    int i=0;
    printf("%d\n",array[0]);
    printf("%d\n",array[size/2]);
    printf("%d\n",array[size-1]);

}
