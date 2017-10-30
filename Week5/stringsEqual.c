// String Equality
// Created by
// Jasvir Boparoy (z5165068)
// Kanadech (King) z5176970
// Created on 2017-08-25
// Tutor's name Zain (F09A)

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TRUE (1 == 1)
#define FALSE (! TRUE)

int stringsEqual (char *stringA, char *stringB);

int main (int argc, char *argv[]) {
    // Some simple assert-based tests.
    // You probably want to write some more.
    assert (stringsEqual ("", "") == TRUE);
    assert (stringsEqual (" ", "") == FALSE);
    assert (stringsEqual ("", " ") == FALSE);
    assert (stringsEqual (" ", " ") == TRUE);
    assert (stringsEqual ("\n", "\n") == TRUE);
    assert (stringsEqual ("This is 17 bytes.", "") == FALSE);
    assert (stringsEqual ("", "This is 17 bytes.") == FALSE);
    assert (stringsEqual ("This is 17 bytes.", "This is 17 bytes.") == TRUE);
    assert (stringsEqual ("Here are 18 bytes!", "This is 17 bytes.") == FALSE);
    assert (stringsEqual ("Here are 18 bytes45456!", "Here are 18 bytes45456!") == TRUE);

    printf ("All tests passed.  You are awesome!\n");

    return EXIT_SUCCESS;
}


// Takes two strings, and if they are the same,
// returns TRUE, or FALSE otherwise.
int stringsEqual (char *stringA, char *stringB) {
    int result = -1, i=0,a1=0,b1=0;
    while(stringA[i]!='\0'){
        a1++;
        i++;
    }
    i=0;
    
    while(stringB[i]!='\0'){
        b1++;
        i++;
    }
    i=0;
    if(a1==b1){
        while((i<a1+1)&&result!=0) {
            if(stringA[i]==stringB[i]){
                result = 1;
            } else {
                result = 0;
                
            }
            i++;
        }
    } else {
        result = 0;
    }
    
    return result;
}
