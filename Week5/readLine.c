// Read a line of input.
// Created by
//  Jasvir Boparoy z5165068
//  Kanadech (King) z5176970
// Created on 2017-08-31
// Tutor's name Zain F09A

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 64

void readLine (int bufferLen, char *buffer);

int main (int argc, char *argv[]) {
    // Declare a buffer.  In this case, we're declaring and using a
    // 64-byte buffer, but this could be any length you like, and in
    // our tests you will be required to handle arrays of any length.
    char buffer[BUFFER_LENGTH] = {0};

    // Read in a line...
    readLine (BUFFER_LENGTH, buffer);

    // ... and print it out.  The `%s` format code prints a string.
    printf ("<%s>\n", buffer);

    return EXIT_SUCCESS;
}

// Reads a line of input into `buffer`, excluding the newline;
// ensures that `buffer` is a null-terminated string.
void readLine (int bufferLen, char *buffer) {
    // Your code goes here!
    int i = 0;
/*
    char c;
    c=getchar();
    while (c != '\n') {
        if(i< bufferLen-1) {
        buffer[i] = c;
        i++;
        }
    c=getchar();
    }
    buffer[i]=0;
*/

    while((i < bufferLen-1) && (buffer[i] = getchar ()) != '\n') {
        i++;
    }
    buffer[i]='\0';

/*
    char c;
    int i=0;
    while( (c = getchar()) != '\n')
    {
        if(i < bufferLen-1) buffer[i++] = c;
    }
    buffer[i] = 0;
*/
    return;
}
