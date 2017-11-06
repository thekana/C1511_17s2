#include <stdio.h>
#include <stdlib.h>

// YOU MAY ALTER THE VALUE OF THE FOLLOWING CONSTANT BUT NOT ITS NAME
#define MAXNUM 3

int main (int argc, char *argv[]) {
    int i = 0;
    int j = 0;
    // YOUR CODE GOES HERE

    printf ("Grid size: %d\n", MAXNUM);

    int numOfPrintsJ = MAXNUM * 2 + 1;
    int numOfPrintsI = MAXNUM + 1;

    while (i < numOfPrintsI) {
        j = 0;
        while (j < numOfPrintsJ) {
            if (j % 2 == 0) {
                printf("+");
            } else {
                printf("-");
            }
            j++;
        }
        printf("\n");

        i++;
    }
    // YOUR CODE GOES HERE

    return EXIT_SUCCESS;
}

// Write a complete C program called grid.c that takes a defined
// constant MAXNUM and prints a MAXNUM × MAXNUM grid using the
// ASCII characters + (plus) and - (minus). Using these two symbols
// a grid cell can be constructed by arranging the characters
// as follows:
// +-+ +-+
// For example, with MAXNUM given the value 3
//     % ./grid
//     Grid size: 3
//     +-+-+-+
//     +-+-+-+
//     +-+-+-+
//     +-+-+-+
