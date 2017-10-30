// How long is a (piece of) string?
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int stringLength (char *string);

int main (int argc, char *argv[]) {
    // Some simple assert-based tests.
    // You probably want to write some more.
    assert (stringLength ("") == 0);
    assert (stringLength ("!") == 1);
    assert (stringLength ("Hello, world!") == 13);
    assert (stringLength ("17... seventeen.\n") == 17);

    printf ("All tests passed.  You are awesome!\n");

    return EXIT_SUCCESS;
}

// Takes a string and finds its length, excluding the null-terminator.
int stringLength (char *string) {
    int L=0, i=0;
    while (string[i] != '\0') {
        i++;
        L++;
    }
    return L;
}

