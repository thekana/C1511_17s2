// Test a string ADT
//  Quinn z5142018
//  King z5176970
// Created on 2017 09 22
// Tutor's name Zain F09A
#include <stdlib.h>
#include <stdio.h>
#include "String.h"

int main (int argc, char* argv[]) {

    String new_string1 = newString("ABCDEFG");
    printf("The length is %d\n",stringLength(new_string1));
    String new_string2 = newString("123");
    printf("The length is %d\n",stringLength(new_string2));
    String combined = stringConcat(new_string1,new_string2);
    printf("The length is %d\n",stringLength(combined));
    printf("Are they equal : %d\n",stringsEqual(new_string1,new_string2));
    char find='B';
    printf("Character %c is at index %d\n",find,stringFindChar (new_string1,find));

    return EXIT_SUCCESS;
}
