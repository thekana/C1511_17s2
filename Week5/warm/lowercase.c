// Print out characters in lower case.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

char lowercase (char c);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {

    // get the character
    int c = getchar ();

    // loop until end of characters
    while (c != EOF) {
        // print the character in lowercase
        putchar (lowercase (c));

        // get the next character
        c = getchar ();
    }

    return EXIT_SUCCESS;
}

// Returns the character `c`, lowercased.
char lowercase (char c) {
    // Your code goes here!
    // Don't forget to return your result.
    if ('A' <= c && c<= 'Z') {
        c=c+32;
    }
    return c;
}
