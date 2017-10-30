// Stub for rotateOne activity.
// Created by ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

char rotateOne (char c);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {

    // get character
    char c = getchar ();

    while (c != EOF) {
        // print rotated characted
        putchar (rotateOne (c));

        // get next character
        c = getchar ();
    }

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

// this function "rotates" letters by one
// by changing a to b, b to c...and z to a
char rotateOne (char c) {
    // Your code goes here!
    // Don't forget to return your result.
    if (('a'<=c && c<='z') || ('A'<=c && c<= 'Z')) {
        if (c == 'Z') {
            c = 'A';
        } else if (c == 'z') {
            c = 'a';
        } else {
            c = c + 1;
        }
    }
    return c;
}

