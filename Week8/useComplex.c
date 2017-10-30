#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Complex.h"

int main (int argc, char *argv[]) {

    Complex w = newComplex (414554.41658, 1235.1541541);
    double re = complexRe (w);
    printf ("The real part is %lf.\n", re);

    return EXIT_SUCCESS;
}
