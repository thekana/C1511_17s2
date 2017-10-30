// Swap two values by pointers.
// Created by ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int *b);

int main (int argc, char *argv[]) {
    // getting two numbers from input
    int num1, num2;
    printf ("Enter two numbers: ");
    scanf ("%d %d", &num1, &num2);

    swap(&num1,&num2);

    printf ("The numbers swapped are %d and %d.\n", num1, num2);

    return EXIT_SUCCESS;
}

// this function swaps the values
// of the two integers, passed in as pointers.
void swap (int *a, int *b) {
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;

}

