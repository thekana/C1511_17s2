// gnirtS a esreveR
// Created by
//  Jasvir Boparoy z5165068
//  Kanadech (King) z5176970
// Created on 2017-08-31
// Tutor's name Zain F09A

#include <stdio.h>
#include <stdlib.h>

void stringReverse (char *buffer);

int main (int argc, char *argv[]) {
    /// THIS WON'T WORK!
    ///
    /// `str` only points to a string literal, which is stored in a
    /// read only section of the program.  If you attempt to modify
    /// it, your program will crash with a memory error (usually,
    /// SIGSEGV, the infamous "segmentation fault").
    //
    // char *str = "Hello!"
    // stringReverse (str)

    char str[] = ".'neetneves' :egassem terces A";
    stringReverse (str);
    printf ("%s\n", str);

    return EXIT_SUCCESS;
}

// Takes a string in `buffer`, and reverses it in-place.
void stringReverse (char *buffer) {
    int count = 0;
    int i = 0;
    char temp;
    while (buffer[i] != '\0') {
        count++;
        i++;
    }
    if (count!=0) {
        char hold[count];

        i=0;
        while (buffer[i] != '\0') {
            hold[i]=buffer[count-i-1];
            i++;
        }
        i=0;
        while (buffer[i] != '\0') {
            buffer[i]=hold[i];
            i++;
        }
    }
}

