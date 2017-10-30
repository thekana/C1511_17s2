// COMP1511 17s2 -- Complex ADT
// Created by: ... (z0000000)
//             ... (z0000000)
// Created on: 2017-09-??
// Tutorial:   dayHH-lab

#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include "Complex.h"

typedef struct _complex {
    double re;
    double im;
} complex;

// Create a new `Complex` number from two `double`s.
Complex newComplex (double re, double im) {
    complex *new = calloc(1, sizeof(complex));
    
    if (new == NULL) {
        exit(EXIT_FAILURE);
    }
    
    new->re = re;
    new->im = im;
     
    return new;
}

// Release all resources associated with a `Complex` number.
void destroyComplex (Complex c) {
    free(c);
}

// Retrieve the real part of the `Complex` number.
double complexRe (Complex c) {
    double real;
    real = c->re;
    
    return real;
}

// Retrieve the imaginary part of the `Complex` number.
double complexIm (Complex c) {
    double imaginary;
    imaginary = c->im;
    
    return imaginary;
}

// Add two `Complex` numbers together.
Complex complexAdd (Complex w, Complex z) {
    Complex added = newComplex(0, 0); 
    
    added->re = w->re + z->re;
    added->im = w->im + z->im;
    
    return added;
}

// Multiply two `Complex` numbers together.
Complex complexMultiply (Complex w, Complex z) {
    Complex multiply = newComplex(0, 0);
    
    multiply->re = w->re * z->im;
    multiply->im = w->im * z->im;
    return multiply;
}

// Take the magnitude (or modulus, or absolute) of a `Complex` number.
double complexMod (Complex w) {
    double mod;
    mod = pow(w->re * w->re + w->im * w->im, 1/2);
    return mod;
}

// Take the argument (or angle) of a `Complex` number.
double complexArg (Complex w) {
    double arg;
    arg = atan2(w->im, w->re);
    return arg;
}
