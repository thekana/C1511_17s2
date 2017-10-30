//  Exploring memory
//  Created by Richard Buckland on 2012-11-20.
//
//  Modified by:
//      Your name (your zID)
//      Your partner's name (your partner's zID)
//
//  YYYY-MM-DD

#include <stdio.h>
#include <stdlib.h>

long add (int x, int y);

int main(int argc, const char * argv[]) {

    int x;
    int y;
    long total;

    x = 40;
    y = 2;

    printf("The size of a int, in bytes, is %lu.\n", sizeof(x));
    printf("The variable x is located at memory address %p.\n", &x);

    total = add (x, y);

    printf("the sum of %d and %d is %ld\n", x, y, total);

    char c ='a';

    unsigned long ul       = 0;
    unsigned int ui        = 1;
    unsigned long long ull = 2;
    unsigned short us      = 3;

    signed long sl       = 4;
    signed int si        = 5;
    signed long long sll = 6;
    signed short ss      = 7;

    long l       = 8;
    int i        = 9;
    long long ll = 10;
    short s      = 11;

    float f = 3.1;
    double d = 3.14;


    return EXIT_SUCCESS;
}

long add (int x, int y) {
    long answer;
    answer = x + y;

    return answer;
}
