// Copy a String
// Created by
//  Jasvir Boparoy z5165068
//  Kanadech (King) z5176970
// Created on 2017-08-31
// Tutor's name Zain F09A

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 64

void stringCopy (char *destination, char *source, int destSize);

int main (int argc, char *argv[]) {
    // Declare a buffer.  In this case, we're declaring and using a
    // 64-byte buffer, but this could be any length you like, and in
    // our tests you will be required to handle arrays of any length.
    char buffer[BUFFER_LENGTH] = {0};

    // Copy a string into the buffer ...
    stringCopy (buffer, "Seventeen bytes.\n", BUFFER_LENGTH);

    // ... and print it out.  The `%s` format code prints a string.
    printf ("<%s>\n", buffer);

    return EXIT_SUCCESS;
}

// Takes a string in `source`, and copies it to `destination`, which
// is `destSize` elements in size; only copies up to `destSize` bytes.
// Ensures the `destination` array is null-terminated.
void stringCopy (char *destination, char *source, int destSize) {
    
    int i=0;
    while(source[i]!='\0'&&(i<destSize-1)) {
        destination[i]=source[i];
        i++;
    }
    destination[i]='\0';
    return;
}

