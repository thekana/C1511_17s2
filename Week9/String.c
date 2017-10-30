// String ADT
//  Quinn z5142018
//  King z5176970
// Created on 2017 09 22
// Tutor's name Zain F09A

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "String.h"

#define FALSE 0
#define TRUE 1
typedef struct _string {
    char *array;
    int length;
} string;

// Create a new `String`, from a C-style null-terminated array of
// characters.
String newString (char *str) {
    //*string == String
    String new = calloc(1, sizeof(string));
    if (new == NULL) {
        fprintf(stderr, "Could not allocate memory\n");
        exit(EXIT_FAILURE);
    }
    int length = 0;
    int i=0;
    while (str[i] != '\0') {
        length++;
        i++;
    }
    new->length=length;
    new->array = calloc(length + 1, sizeof(char));
    i=0;
    while(i<length) {
        new->array[i]=str[i];
        i++;
    }
    new->array[i] = '\0';
    return new;
}

// Release all resources associated with a `String`.
void destroyString (String s) {
    free(s->array);
    free(s);
}
// Get the length of a `String`.
int stringLength (String s) {
    return s->length;
}


// Make a (mutable) copy of a `String`.
String stringClone (String s) {
    return newString(s->array);
}

// Given a `String`, and an index in the `String`, return the
// character at that index.
char stringAt (String s, int index){
    return s->array[index];
}

// Given a `String`, and a character to look for in the `String`,
// return either the index of the character, or `-1` if the character
// could not be found in the `String`.
int stringFindChar (String s, char find){
    int answer= FALSE;
    int i=0;
    while(answer == FALSE && s->array[i] != '\0'){
        if(s->array[i] == find) {
            answer = i;
        }
        i++;
    }
    return answer;
}
// Are two `String`s equal?
int stringsEqual (String s1, String s2) {
    int answer=TRUE;
    if(s1->length != s2->length) {
        answer = FALSE;
    }
    int i=0;
    while (answer == TRUE && i<(s1->length)){
        if (s1->array[i]==s2->array[i]){
            answer = TRUE;
        } else {
            answer = FALSE;
        }
        i++;
    }
    return answer;
}
// Given two `String`s, concatenates them into a new `String`.
String stringConcat (String s1, String s2) {
    int newLength = s1->length + s2->length;
    int i=0,j=0;
    //char newStr[newLength + 1];
    char * concat = calloc(newLength + 1, sizeof(char));
    while(i< s1->length) {
        concat[i] = s1->array[i];
        i++;
    }
    while(j < s2->length) {
        concat[i+j] = s2->array[j];
        j++;
    }
    String new = newString(concat);
    free(concat);
    return new;
}

