//  Exploring memory
//  Created by Richard Buckland on 2012-11-20.
//
//  Modified by:
//      Kanadech Jirapongtanavech (z5176970)
//      JIAYI SI (z5142102)
//
//  2017-08-18

#include <stdio.h>
#include <stdlib.h>

long add (int x, int y);
unsigned long long loopsign (unsigned long long byte);
unsigned long long loopunsign (unsigned long long byte);

int main(int argc, const char * argv[]) {

    int x;
    int y;
    long total;

    x = 40;
    y = 2;

    printf("The size of a int, in bytes, is %d.\n", sizeof(x));
    printf("The variable x is located at memory address %p.\n", &x);

    total = add (x, y);

    printf("the sum of %d and %d is %ld\n", x, y, total);

    char c ='a';
    unsigned char cc = 'b';
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

    // add them all together just to make use of them so the compiler
    // doesn't grumble that they are unused in the program

    double grandTotal=0;
    grandTotal =  c + cc +
        ul + ui + ull + us +
        sl + si + sll + ss +
        l +  i +  ll +  s +
        f + d;

    printf("all these things added together make %f\n",
        grandTotal);

    printf("The biggest number for int is %lu\n", loopsign(sizeof(x)));
    printf("The smallest number for int is %d\n\n", loopsign(sizeof(x))+1);

    printf("The size of a char, in bytes is %d.\n", sizeof(c));
    printf("The variable c is located at memory address %p.\n", &c);
    printf("The biggest number for char is %hhd\n", loopsign(sizeof(c)));
    printf("The smallest number for char is %hhd\n\n", loopsign(sizeof(c))+1);

    printf("The size of a unsigned char, in bytes is %d.\n", sizeof(cc));
    printf("The variable c is located at memory address %p.\n", &cc);
    printf("The biggest number for char is %hhu\n", loopunsign(sizeof(cc)));
    printf("The smallest number for char is %hhu\n\n", loopunsign(sizeof(cc))+1);


    printf("The size of a unsigned long is %d\n", sizeof(ul));
    printf("The variable ul is located at memory address %p \n", &ul);
    printf("The biggest number for unsigned long is %llu\n", loopunsign(sizeof(ul)));
    printf("The smallest number for unsigned long is %lu\n\n", loopunsign(sizeof(ul))+1);

    printf("The size of a unsigned int is %d\n", sizeof(ui));
    printf("The variable ui is located at memory address %p \n", &ui);
    printf("The biggest number for unsigned int is %llu\n", loopunsign(sizeof(ui)));
    printf("The smallest number for unsigned int is %u\n\n", loopunsign(sizeof(ui))+1);

    printf("The size of a unsigned long long is %d\n", sizeof(ull));
    printf("The variable ull is located at memory address %p \n", &ull);
    printf("The biggest number for unsigned long long is %llu\n", loopunsign(sizeof(ull)));
    printf("The smallest number for unsigned long long is %llu\n\n", loopunsign(sizeof(ull))+1);


    printf("The size of a unsigned short is %d\n", sizeof(us));
    printf("The variable us is located at memory address %p \n", &us);
    printf("The biggest number for unsigned short is %llu\n", loopunsign(sizeof(us)));
    printf("The smallest number for unsigned short is %hu\n\n", loopunsign(sizeof(us))+1);

    //========================================================//
    printf("The size of a long, in bytes, is %d.\n", sizeof(l));
    printf("The long l is located at memory address %p.\n", &l);
    printf("The biggest number for long is %llu\n", loopsign(sizeof(l)));
    printf("The smallest number for long is %ld\n\n", loopsign(sizeof(l))+1);

    printf("The size of a int, in bytes, is %d.\n", sizeof(i));
    printf("The int i is located at memory address %p.\n", &i);
    printf("The biggest number for int is %llu\n", loopsign(sizeof(i)));
    printf("The smallest number for int is %d\n\n", loopsign(sizeof(i))+1);

    printf("The size of a long long, in bytes, is %d.\n", sizeof(ll));
    printf("The long long ll is located at memory address %p.\n", &ll);
    printf("The biggest number for long long is %lld\n", loopsign(sizeof(ll)));
    printf("The smallest number for long long is %lld\n\n", loopsign(sizeof(ll))+1);

    printf("The size of a short, in bytes, is %d.\n", sizeof(s));
    printf("The short s is located at memory address %p.\n", &s);
    printf("The biggest number for short is %hd\n", loopsign(sizeof(s)));
    printf("The smallest number for short is %hd\n\n", loopsign(sizeof(s))+1);

    printf("The size of a float, in bytes, is %d.\n", sizeof(f));
    printf("The float f is located at memory address %p.\n", &f);
    printf("The biggest number for float is %f\n", 1.7E308*1.1);
    printf("The smallest number for float is %f\n\n", -1.7E308*1.1);

    printf("The size of a double, in bytes, is %d.\n", sizeof(d));
    printf("The double d is located at memory address %p.\n", &d);
    printf("The biggest number for double is %lf\n", 1.7E308*1.1);
    printf("The smallest number for double is %lf\n\n", -1.7E308*1.1);



    return EXIT_SUCCESS;
}


unsigned long long loopsign (unsigned long long byte){

    unsigned long long n,num=1,i=0,a,bits;
    bits=byte*8;
    while(i<bits){
        num=num*2;
        i++;
    }
    num=(num-2)/2;
    return num;
}

unsigned long long loopunsign (unsigned long long byte){

    unsigned long long n,num=1,i=0,a,bits;
    bits=byte*8;
    while(i<bits){
        num=num*2;
        i++;
    }
    num=num-1;
    return num;
}

long add (int x, int y) {
    long answer;
    answer = x + y;

    return answer;
}

