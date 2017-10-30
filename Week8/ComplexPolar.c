// COMP1511 17s2 -- Complex ADT
// Created by: ... (z0000000)
//             ... (z0000000)
// Created on: 2017-09-??
// Tutorial:   dayHH-lab
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

#include "Complex.h"

typedef struct _complex {
    double mod;
    double arg;
} complex;


// Create a new `Complex` number from two `double`s.


static Complex newComplexModArg (double mod, double arg) {
    complex *c = calloc (1, sizeof (complex));
    if (c == NULL) {
        printf ("Complex: couldn't allocate memory\n");
        exit (1);
    }
    c->mod = mod;
    c->arg = arg;
    return c;
}


// Release all resources associated with a `Complex` number.
void destroyComplex (Complex c) {
    free(c);
}


// Multiply two `Complex` numbers together.
Complex complexMultiply (Complex w, Complex z) {
    Complex multiply = newComplex(0, 0);
    
    multiply->mod = w->mod * z->mod;
    multiply->arg = (w->arg + z->arg);
    return multiply;
}

