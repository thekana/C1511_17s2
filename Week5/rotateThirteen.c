// Perform the ROT13 algorithm on a string
// Created by
//  Jasvir Boparoy z5165068
//  Kanadech (King) z5176970
// Created on 2017-08-31
// Tutor's name Zain F09A

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE (!FALSE)
#define MAX_LENGTH 256

// Add your own #defines here

void rotateThirteen (char *string);
char rotateOne (char c);
int stringLength (char *string);
int stringsEqual (char *stringA, char *stringB);

// Add your own function porototypes here

int main (int argc, char *argv[]) {
    // Example tests
    char testA[MAX_LENGTH] = "Hello, world!";
    rotateThirteen (testA);

    assert (stringsEqual ("Uryyb, jbeyq!", testA));

    char testB[MAX_LENGTH] = "abcdefghijklmnopqrstuvwxyzOA";
    rotateThirteen (testB);
    assert (stringsEqual ("nopqrstuvwxyzabcdefghijklmBN", testB));

    char testC[MAX_LENGTH] = "The quick brown fox jumped over the lazy dog.";
    rotateThirteen (testC);

    assert (stringsEqual ("Gur dhvpx oebja sbk whzcrq bire gur ynml qbt.", testC));
    //char testD[MAX_LENGTH] = "ABCDEFGHIJKLMNOP\nabcdegfh";
    //rotateThirteen (testD);
    //printf("%s\n",testD);

    // Add your own tests here

    printf ("All tests passed. You are awesome!\n");

    return EXIT_SUCCESS;
}

void rotateThirteen (char *string) {

    int i = 0;
    while (string[i] != '\0') {
        char c=string[i];
        if ('a'<=c && c<='z') {
            if(c>'m') {
                string[i]-=13;
            } else {
                string[i]+=13;
            }
        } else if ('A'<=c && c<= 'Z') {
            if(c>'M') {
                string[i]-=13;
            } else {
                string[i]+=13;
            }
        } else {
            string[i] = c;
        }
        i++;
    }
}

char rotateOne (char c) {

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

int stringLength (char *string) {
    int i=0,count=0;
    while (string[i] != '\0') {
        count++;
        i++;
    }
    return count;
}

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

