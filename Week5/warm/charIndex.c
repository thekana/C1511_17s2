// Find the index of a character in a given string.
// Created by
//  ... (z0000000)
//  ... (z0000000)
// Created on 2017-08-??
// Tutor's name (dayHH-lab)

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_LENGTH 1024
#define NOT_IN_STRING -1

void readLine (int bufferLen, char *buffer);
int charIndex (char c, char *string);

// DO NOT CHANGE THIS MAIN FUNCTION
int main (int argc, char *argv[]) {
    // Declare a buffer
    char buffer[BUFFER_LENGTH] = {0};

    // Read in a line...
    printf ("Enter a line: ");
    readLine (BUFFER_LENGTH, buffer);

    // Get a character
    char ch;
    printf ("Enter a character: ");
    scanf ("%c", &ch);

    // Find and print character index or "not in string"
    int index = charIndex (ch, buffer);
    if (index == NOT_IN_STRING) {
        printf ("Character '%c' is not in the string.\n", ch);
    } else {
        printf ("Index of character '%c': %d\n", ch, index);
    }

    return EXIT_SUCCESS;
}
// END OF MAIN FUNCTION

// Read a line of input into `buffer`, excluding the newline;
// ensures that `buffer` is a null-terminated string.
void readLine (int bufferLen, char *buffer) {
    int i=0;
    while((i < bufferLen-1) && (buffer[i] = getchar ()) != '\n') {
        i++;
    }
    buffer[i]='\0';
}

// Return the index of the first occurrence of
// character `c` in the string, or `NOT_IN_STRING`
int charIndex (char c, char *string) {
    // Your code goes here!
    // Don't forget to return your result.
    int result=-1, i=0;
    while(result <= -1 && string[i] != '\0') {
        if(string[i]==c) {
            result=i;
        }
        i++;
    }
    return result;
}

